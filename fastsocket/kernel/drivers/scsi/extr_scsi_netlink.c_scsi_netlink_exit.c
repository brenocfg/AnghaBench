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

/* Variables and functions */
 int /*<<< orphan*/  SCSI_NL_TRANSPORT ; 
 int /*<<< orphan*/  netlink_kernel_release (scalar_t__) ; 
 int /*<<< orphan*/  netlink_unregister_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_netlink_notifier ; 
 int /*<<< orphan*/  scsi_nl_remove_transport (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_nl_sock ; 

void
scsi_netlink_exit(void)
{
	scsi_nl_remove_transport(SCSI_NL_TRANSPORT);

	if (scsi_nl_sock) {
		netlink_kernel_release(scsi_nl_sock);
		netlink_unregister_notifier(&scsi_netlink_notifier);
	}

	return;
}