#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zoneid_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uid_t ;
struct TYPE_7__ {TYPE_1__* dtpr_provider; } ;
typedef  TYPE_3__ dtrace_probe_t ;
struct TYPE_6__ {int dtpp_flags; scalar_t__ dtpp_uid; scalar_t__ dtpp_zoneid; } ;
struct TYPE_5__ {TYPE_2__ dtpv_priv; } ;

/* Variables and functions */
 int DTRACE_PRIV_ALL ; 
 int DTRACE_PRIV_KERNEL ; 
 int DTRACE_PRIV_OWNER ; 
 int DTRACE_PRIV_PROC ; 
 int DTRACE_PRIV_USER ; 
 int DTRACE_PRIV_ZONEOWNER ; 

__attribute__((used)) static int
dtrace_match_priv(const dtrace_probe_t *prp, uint32_t priv, uid_t uid,
    zoneid_t zoneid)
{
	if (priv != DTRACE_PRIV_ALL) {
		uint32_t ppriv = prp->dtpr_provider->dtpv_priv.dtpp_flags;
		uint32_t match = priv & ppriv;

		/*
		 * No PRIV_DTRACE_* privileges...
		 */
		if ((priv & (DTRACE_PRIV_PROC | DTRACE_PRIV_USER |
		    DTRACE_PRIV_KERNEL)) == 0)
			return (0);

		/*
		 * No matching bits, but there were bits to match...
		 */
		if (match == 0 && ppriv != 0)
			return (0);

		/*
		 * Need to have permissions to the process, but don't...
		 */
		if (((ppriv & ~match) & DTRACE_PRIV_OWNER) != 0 &&
		    uid != prp->dtpr_provider->dtpv_priv.dtpp_uid) {
			return (0);
		}

		/*
		 * Need to be in the same zone unless we possess the
		 * privilege to examine all zones.
		 */
		if (((ppriv & ~match) & DTRACE_PRIV_ZONEOWNER) != 0 &&
		    zoneid != prp->dtpr_provider->dtpv_priv.dtpp_zoneid) {
			return (0);
		}
	}

	return (1);
}