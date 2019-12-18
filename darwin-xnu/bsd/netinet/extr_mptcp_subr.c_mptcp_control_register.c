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
struct kern_ctl_reg {int /*<<< orphan*/  ctl_flags; int /*<<< orphan*/  ctl_send; int /*<<< orphan*/  ctl_disconnect; int /*<<< orphan*/  ctl_connect; int /*<<< orphan*/  ctl_name; } ;
typedef  int /*<<< orphan*/  mptcp_kern_ctl ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_PRIVILEGED ; 
 int /*<<< orphan*/  MPTCP_KERN_CTL_NAME ; 
 int /*<<< orphan*/  bzero (struct kern_ctl_reg*,int) ; 
 int /*<<< orphan*/  ctl_register (struct kern_ctl_reg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mptcp_kern_ctrl_ref ; 
 int /*<<< orphan*/  mptcp_symptoms_ctl_connect ; 
 int /*<<< orphan*/  mptcp_symptoms_ctl_disconnect ; 
 int /*<<< orphan*/  mptcp_symptoms_ctl_send ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
mptcp_control_register(void)
{
	/* Set up the advisory control socket */
	struct kern_ctl_reg mptcp_kern_ctl;

	bzero(&mptcp_kern_ctl, sizeof(mptcp_kern_ctl));
	strlcpy(mptcp_kern_ctl.ctl_name, MPTCP_KERN_CTL_NAME,
	    sizeof(mptcp_kern_ctl.ctl_name));
	mptcp_kern_ctl.ctl_connect = mptcp_symptoms_ctl_connect;
	mptcp_kern_ctl.ctl_disconnect = mptcp_symptoms_ctl_disconnect;
	mptcp_kern_ctl.ctl_send = mptcp_symptoms_ctl_send;
	mptcp_kern_ctl.ctl_flags = CTL_FLAG_PRIVILEGED;

	(void)ctl_register(&mptcp_kern_ctl, &mptcp_kern_ctrl_ref);
}