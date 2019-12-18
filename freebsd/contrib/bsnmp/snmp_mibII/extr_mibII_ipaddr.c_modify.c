#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int s_addr; } ;
struct TYPE_5__ {int s_addr; } ;
struct update {int set; scalar_t__ ifindex; int /*<<< orphan*/  rb; TYPE_3__ rb_bcast; TYPE_2__ rb_mask; scalar_t__ bcast; TYPE_2__ mask; } ;
struct TYPE_4__ {int s_addr; } ;
struct mibifa {scalar_t__ ifindex; TYPE_3__ inbcast; TYPE_2__ inmask; TYPE_1__ inaddr; } ;
struct mibif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  RB_MODIFY ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_WRONG_VALUE ; 
 int UPD_BCAST ; 
 int UPD_IFINDEX ; 
 int UPD_MASK ; 
 struct mibif* mib_find_if (scalar_t__) ; 
 scalar_t__ mib_modify_ifa (struct mibifa*) ; 
 int /*<<< orphan*/  mib_unmodify_ifa (struct mibifa*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
modify(struct update *upd, struct mibifa *ifa)
{
	struct mibif *ifp;

	if ((ifp = mib_find_if(ifa->ifindex)) == NULL)
		return (SNMP_ERR_WRONG_VALUE);
	if ((upd->set & UPD_IFINDEX) && upd->ifindex != ifa->ifindex)
		return (SNMP_ERR_INCONS_VALUE);

	upd->rb_mask = ifa->inmask;
	upd->rb_bcast = ifa->inbcast;
	if (((upd->set & UPD_MASK) && upd->mask.s_addr != ifa->inmask.s_addr) ||
	    (upd->set & UPD_BCAST)) {
		if (upd->set & UPD_MASK)
			ifa->inmask = upd->mask;
		if (upd->set & UPD_BCAST) {
			ifa->inbcast.s_addr = ifa->inaddr.s_addr
			    & ifa->inmask.s_addr;
			if (upd->bcast)
				ifa->inbcast.s_addr |= 0xffffffff
				    & ~ifa->inmask.s_addr;
		}
		if (mib_modify_ifa(ifa)) {
			syslog(LOG_ERR, "set netmask/bcast: %m");
			ifa->inmask = upd->rb_mask;
			ifa->inbcast = upd->rb_bcast;
			mib_unmodify_ifa(ifa);
			return (SNMP_ERR_GENERR);
		}
		upd->rb |= RB_MODIFY;
	}
	return (SNMP_ERR_NOERROR);
}