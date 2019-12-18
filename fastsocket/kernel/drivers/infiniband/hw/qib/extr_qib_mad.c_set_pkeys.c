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
typedef  int u8 ;
typedef  int u16 ;
struct qib_pportdata {size_t hw_pidx; } ;
struct TYPE_3__ {int /*<<< orphan*/  ibdev; } ;
struct qib_devdata {TYPE_1__ verbs_dev; int /*<<< orphan*/  (* f_set_ib_cfg ) (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct qib_ctxtdata** rcd; struct qib_pportdata* pport; } ;
struct qib_ctxtdata {int* pkeys; } ;
struct TYPE_4__ {int port_num; } ;
struct ib_event {TYPE_2__ element; int /*<<< orphan*/ * device; int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  IB_EVENT_PKEY_CHANGE ; 
 int /*<<< orphan*/  QIB_IB_CFG_PKEYS ; 
 int add_pkey (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int rm_pkey (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  stub1 (struct qib_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_pkeys(struct qib_devdata *dd, u8 port, u16 *pkeys)
{
	struct qib_pportdata *ppd;
	struct qib_ctxtdata *rcd;
	int i;
	int changed = 0;

	/*
	 * IB port one/two always maps to context zero/one,
	 * always a kernel context, no locking needed
	 * If we get here with ppd setup, no need to check
	 * that rcd is valid.
	 */
	ppd = dd->pport + (port - 1);
	rcd = dd->rcd[ppd->hw_pidx];

	for (i = 0; i < ARRAY_SIZE(rcd->pkeys); i++) {
		u16 key = pkeys[i];
		u16 okey = rcd->pkeys[i];

		if (key == okey)
			continue;
		/*
		 * The value of this PKEY table entry is changing.
		 * Remove the old entry in the hardware's array of PKEYs.
		 */
		if (okey & 0x7FFF)
			changed |= rm_pkey(ppd, okey);
		if (key & 0x7FFF) {
			int ret = add_pkey(ppd, key);

			if (ret < 0)
				key = 0;
			else
				changed |= ret;
		}
		rcd->pkeys[i] = key;
	}
	if (changed) {
		struct ib_event event;

		(void) dd->f_set_ib_cfg(ppd, QIB_IB_CFG_PKEYS, 0);

		event.event = IB_EVENT_PKEY_CHANGE;
		event.device = &dd->verbs_dev.ibdev;
		event.element.port_num = 1;
		ib_dispatch_event(&event);
	}
	return 0;
}