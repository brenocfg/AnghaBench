#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct net_event_data {int if_unit; TYPE_1__* dv; int /*<<< orphan*/  if_family; int /*<<< orphan*/ * if_name; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
struct kev_msg {int if_unit; TYPE_1__* dv; int /*<<< orphan*/  if_family; int /*<<< orphan*/ * if_name; int /*<<< orphan*/  event_code; int /*<<< orphan*/  kev_subclass; int /*<<< orphan*/  kev_class; int /*<<< orphan*/  vendor_code; } ;
typedef  TYPE_2__* ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_8__ {int if_capenable; int if_capabilities; scalar_t__ if_unit; int /*<<< orphan*/  if_family; int /*<<< orphan*/  if_name; } ;
struct TYPE_7__ {int data_length; struct net_event_data* data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IFCAP_VALID ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  KEV_DL_IFCAP_CHANGED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 int /*<<< orphan*/  KEV_NETWORK_CLASS ; 
 int /*<<< orphan*/  KEV_VENDOR_APPLE ; 
 int /*<<< orphan*/  bzero (struct net_event_data*,int) ; 
 int /*<<< orphan*/  dlil_post_complete_msg (TYPE_2__*,struct net_event_data*) ; 
 int /*<<< orphan*/  ifnet_lock_done (TYPE_2__*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
ifnet_set_capabilities_enabled(ifnet_t ifp, u_int32_t new_caps,
    u_int32_t mask)
{
	errno_t error = 0;
	int tmp;
	struct kev_msg ev_msg;
	struct net_event_data ev_data;

	if (ifp == NULL)
		return (EINVAL);

	ifnet_lock_exclusive(ifp);
	tmp = (new_caps & mask) | (ifp->if_capenable & ~mask);
	if ((tmp & ~IFCAP_VALID) || (tmp & ~ifp->if_capabilities))
		error = EINVAL;
	else
		ifp->if_capenable = tmp;
	ifnet_lock_done(ifp);

	/* Notify application of the change */
	bzero(&ev_data, sizeof (struct net_event_data));
	bzero(&ev_msg, sizeof (struct kev_msg));
	ev_msg.vendor_code	= KEV_VENDOR_APPLE;
	ev_msg.kev_class	= KEV_NETWORK_CLASS;
	ev_msg.kev_subclass	= KEV_DL_SUBCLASS;

	ev_msg.event_code	= KEV_DL_IFCAP_CHANGED;
	strlcpy(&ev_data.if_name[0], ifp->if_name, IFNAMSIZ);
	ev_data.if_family	= ifp->if_family;
	ev_data.if_unit		= (u_int32_t)ifp->if_unit;
	ev_msg.dv[0].data_length = sizeof (struct net_event_data);
	ev_msg.dv[0].data_ptr = &ev_data;
	ev_msg.dv[1].data_length = 0;
	dlil_post_complete_msg(ifp, &ev_msg);

	return (error);
}