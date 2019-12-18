#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifnet {int dummy; } ;
struct ifmediareq {scalar_t__ ifm_count; int ifm_status; int /*<<< orphan*/  ifm_name; } ;
typedef  int /*<<< orphan*/  ifmr ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int IFM_AVALID ; 
 int /*<<< orphan*/  KEV_DL_LINK_OFF ; 
 int /*<<< orphan*/  KEV_DL_LINK_ON ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  bzero (struct ifmediareq*,int) ; 
 scalar_t__ ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifmediareq*) ; 
 char* ifnet_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  interface_link_event (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlan_link_event(struct ifnet * ifp, struct ifnet * p)
{
    struct ifmediareq ifmr;

    /* generate a link event based on the state of the underlying interface */
    bzero(&ifmr, sizeof(ifmr));
    snprintf(ifmr.ifm_name, sizeof(ifmr.ifm_name),
	     "%s%d", ifnet_name(p), ifnet_unit(p));
    if (ifnet_ioctl(p, 0, SIOCGIFMEDIA, &ifmr) == 0
	&& ifmr.ifm_count > 0 && ifmr.ifm_status & IFM_AVALID) {
	u_int32_t	event;
	
	event = (ifmr.ifm_status & IFM_ACTIVE)
	    ? KEV_DL_LINK_ON : KEV_DL_LINK_OFF;
	interface_link_event(ifp, event);
    }
    return;
}