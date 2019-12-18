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
struct isci_remote_device {int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCI_DEV_READY ; 
 scalar_t__ is_remote_device_ready (struct isci_remote_device*) ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remote_device_resume_done(void *_dev)
{
	struct isci_remote_device *idev = _dev;

	if (is_remote_device_ready(idev))
		return;

	/* go 'ready' if we are not already in a ready state */
	sci_change_state(&idev->sm, SCI_DEV_READY);
}