#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u16 ;
struct ipath_portdata {int* port_pkeys; int /*<<< orphan*/  port_port; struct ipath_devdata* port_dd; } ;
struct ipath_devdata {int* ipath_pkeys; TYPE_1__* ipath_kregs; int /*<<< orphan*/ * ipath_pkeyrefs; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_4__ {int* sps_pkeys; } ;
struct TYPE_3__ {int /*<<< orphan*/  kr_partitionkey; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EBUSY ; 
 int EEXIST ; 
 int EINVAL ; 
 int IPATH_DEFAULT_P_KEY ; 
 int /*<<< orphan*/  PROC ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ipath_dbg (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ ipath_stats ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipath_set_part_key(struct ipath_portdata *pd, u16 key)
{
	struct ipath_devdata *dd = pd->port_dd;
	int i, any = 0, pidx = -1;
	u16 lkey = key & 0x7FFF;
	int ret;

	if (lkey == (IPATH_DEFAULT_P_KEY & 0x7FFF)) {
		/* nothing to do; this key always valid */
		ret = 0;
		goto bail;
	}

	ipath_cdbg(VERBOSE, "p%u try to set pkey %hx, current keys "
		   "%hx:%x %hx:%x %hx:%x %hx:%x\n",
		   pd->port_port, key, dd->ipath_pkeys[0],
		   atomic_read(&dd->ipath_pkeyrefs[0]), dd->ipath_pkeys[1],
		   atomic_read(&dd->ipath_pkeyrefs[1]), dd->ipath_pkeys[2],
		   atomic_read(&dd->ipath_pkeyrefs[2]), dd->ipath_pkeys[3],
		   atomic_read(&dd->ipath_pkeyrefs[3]));

	if (!lkey) {
		ipath_cdbg(PROC, "p%u tries to set key 0, not allowed\n",
			   pd->port_port);
		ret = -EINVAL;
		goto bail;
	}

	/*
	 * Set the full membership bit, because it has to be
	 * set in the register or the packet, and it seems
	 * cleaner to set in the register than to force all
	 * callers to set it. (see bug 4331)
	 */
	key |= 0x8000;

	for (i = 0; i < ARRAY_SIZE(pd->port_pkeys); i++) {
		if (!pd->port_pkeys[i] && pidx == -1)
			pidx = i;
		if (pd->port_pkeys[i] == key) {
			ipath_cdbg(VERBOSE, "p%u tries to set same pkey "
				   "(%x) more than once\n",
				   pd->port_port, key);
			ret = -EEXIST;
			goto bail;
		}
	}
	if (pidx == -1) {
		ipath_dbg("All pkeys for port %u already in use, "
			  "can't set %x\n", pd->port_port, key);
		ret = -EBUSY;
		goto bail;
	}
	for (any = i = 0; i < ARRAY_SIZE(dd->ipath_pkeys); i++) {
		if (!dd->ipath_pkeys[i]) {
			any++;
			continue;
		}
		if (dd->ipath_pkeys[i] == key) {
			atomic_t *pkrefs = &dd->ipath_pkeyrefs[i];

			if (atomic_inc_return(pkrefs) > 1) {
				pd->port_pkeys[pidx] = key;
				ipath_cdbg(VERBOSE, "p%u set key %x "
					   "matches #%d, count now %d\n",
					   pd->port_port, key, i,
					   atomic_read(pkrefs));
				ret = 0;
				goto bail;
			} else {
				/*
				 * lost race, decrement count, catch below
				 */
				atomic_dec(pkrefs);
				ipath_cdbg(VERBOSE, "Lost race, count was "
					   "0, after dec, it's %d\n",
					   atomic_read(pkrefs));
				any++;
			}
		}
		if ((dd->ipath_pkeys[i] & 0x7FFF) == lkey) {
			/*
			 * It makes no sense to have both the limited and
			 * full membership PKEY set at the same time since
			 * the unlimited one will disable the limited one.
			 */
			ret = -EEXIST;
			goto bail;
		}
	}
	if (!any) {
		ipath_dbg("port %u, all pkeys already in use, "
			  "can't set %x\n", pd->port_port, key);
		ret = -EBUSY;
		goto bail;
	}
	for (any = i = 0; i < ARRAY_SIZE(dd->ipath_pkeys); i++) {
		if (!dd->ipath_pkeys[i] &&
		    atomic_inc_return(&dd->ipath_pkeyrefs[i]) == 1) {
			u64 pkey;

			/* for ipathstats, etc. */
			ipath_stats.sps_pkeys[i] = lkey;
			pd->port_pkeys[pidx] = dd->ipath_pkeys[i] = key;
			pkey =
				(u64) dd->ipath_pkeys[0] |
				((u64) dd->ipath_pkeys[1] << 16) |
				((u64) dd->ipath_pkeys[2] << 32) |
				((u64) dd->ipath_pkeys[3] << 48);
			ipath_cdbg(PROC, "p%u set key %x in #%d, "
				   "portidx %d, new pkey reg %llx\n",
				   pd->port_port, key, i, pidx,
				   (unsigned long long) pkey);
			ipath_write_kreg(
				dd, dd->ipath_kregs->kr_partitionkey, pkey);

			ret = 0;
			goto bail;
		}
	}
	ipath_dbg("port %u, all pkeys already in use 2nd pass, "
		  "can't set %x\n", pd->port_port, key);
	ret = -EBUSY;

bail:
	return ret;
}