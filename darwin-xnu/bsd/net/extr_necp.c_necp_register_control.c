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
struct kern_ctl_reg {int ctl_sendsize; int ctl_recvsize; int /*<<< orphan*/  ctl_getopt; int /*<<< orphan*/  ctl_setopt; int /*<<< orphan*/  ctl_rcvd; int /*<<< orphan*/  ctl_send; int /*<<< orphan*/  ctl_disconnect; int /*<<< orphan*/  ctl_connect; int /*<<< orphan*/  ctl_flags; scalar_t__* ctl_name; } ;
typedef  int /*<<< orphan*/  kern_ctl ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_FLAG_PRIVILEGED ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  NECP_CONTROL_NAME ; 
 int /*<<< orphan*/  OSMT_DEFAULT ; 
 int /*<<< orphan*/  OSMalloc_Tagalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct kern_ctl_reg*,int) ; 
 scalar_t__ ctl_register (struct kern_ctl_reg*,int /*<<< orphan*/ *) ; 
 scalar_t__ mbuf_tag_id_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  necp_ctl_connect ; 
 int /*<<< orphan*/  necp_ctl_disconnect ; 
 int /*<<< orphan*/  necp_ctl_getopt ; 
 int /*<<< orphan*/  necp_ctl_rcvd ; 
 int /*<<< orphan*/  necp_ctl_send ; 
 int /*<<< orphan*/  necp_ctl_setopt ; 
 int /*<<< orphan*/  necp_family ; 
 int /*<<< orphan*/  necp_kctlref ; 
 int /*<<< orphan*/  necp_malloc_tag ; 
 int /*<<< orphan*/  strlcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static errno_t
necp_register_control(void)
{
	struct kern_ctl_reg	kern_ctl;
	errno_t				result = 0;

	// Create a tag to allocate memory
	necp_malloc_tag = OSMalloc_Tagalloc(NECP_CONTROL_NAME, OSMT_DEFAULT);

	// Find a unique value for our interface family
	result = mbuf_tag_id_find(NECP_CONTROL_NAME, &necp_family);
	if (result != 0) {
		NECPLOG(LOG_ERR, "mbuf_tag_id_find_internal failed: %d", result);
		return (result);
	}

	bzero(&kern_ctl, sizeof(kern_ctl));
	strlcpy(kern_ctl.ctl_name, NECP_CONTROL_NAME, sizeof(kern_ctl.ctl_name));
	kern_ctl.ctl_name[sizeof(kern_ctl.ctl_name) - 1] = 0;
	kern_ctl.ctl_flags = CTL_FLAG_PRIVILEGED; // Require root
	kern_ctl.ctl_sendsize = 64 * 1024;
	kern_ctl.ctl_recvsize = 64 * 1024;
	kern_ctl.ctl_connect = necp_ctl_connect;
	kern_ctl.ctl_disconnect = necp_ctl_disconnect;
	kern_ctl.ctl_send = necp_ctl_send;
	kern_ctl.ctl_rcvd = necp_ctl_rcvd;
	kern_ctl.ctl_setopt = necp_ctl_setopt;
	kern_ctl.ctl_getopt = necp_ctl_getopt;

	result = ctl_register(&kern_ctl, &necp_kctlref);
	if (result != 0) {
		NECPLOG(LOG_ERR, "ctl_register failed: %d", result);
		return (result);
	}

	return (0);
}