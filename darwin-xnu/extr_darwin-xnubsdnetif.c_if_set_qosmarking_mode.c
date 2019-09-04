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
typedef  int u_int32_t ;
struct kev_dl_rrc_state {int dummy; } ;
struct ifnet {int if_qosmarking_mode; int /*<<< orphan*/  if_eflags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFEF_QOSMARKING_CAPABLE ; 
 int /*<<< orphan*/  IFEF_QOSMARKING_ENABLED ; 
#define  IFRTYPE_QOSMARKING_FASTLANE 129 
#define  IFRTYPE_QOSMARKING_MODE_NONE 128 
 int /*<<< orphan*/  KEV_DL_QOS_MODE_CHANGED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 int /*<<< orphan*/  dlil_post_msg (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_qos_policy_capable_enabled ; 

int
if_set_qosmarking_mode(struct ifnet *ifp, u_int32_t mode)
{
	int error = 0;
	u_int32_t old_mode = ifp->if_qosmarking_mode;

	switch (mode) {
		case IFRTYPE_QOSMARKING_MODE_NONE:
			ifp->if_qosmarking_mode = IFRTYPE_QOSMARKING_MODE_NONE;
			ifp->if_eflags &= ~IFEF_QOSMARKING_CAPABLE;
			break;
		case IFRTYPE_QOSMARKING_FASTLANE:
			ifp->if_qosmarking_mode = IFRTYPE_QOSMARKING_FASTLANE;
			ifp->if_eflags |= IFEF_QOSMARKING_CAPABLE;
			if (net_qos_policy_capable_enabled != 0)
				ifp->if_eflags |= IFEF_QOSMARKING_ENABLED;
			break;
		default:
			error = EINVAL;
			break;
	}
	if (error == 0 && old_mode != ifp->if_qosmarking_mode) {
		dlil_post_msg(ifp, KEV_DL_SUBCLASS, KEV_DL_QOS_MODE_CHANGED,
		    NULL, sizeof(struct kev_dl_rrc_state));

	}
	return (error);
}