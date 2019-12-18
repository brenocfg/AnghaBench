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
struct pwc_device {scalar_t__ iso_init; scalar_t__ error_status; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  PWC_DEBUG_OPEN (char*) ; 
 int /*<<< orphan*/  pwc_iso_free (struct pwc_device*) ; 
 int /*<<< orphan*/  pwc_iso_stop (struct pwc_device*) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pwc_isoc_cleanup(struct pwc_device *pdev)
{
	PWC_DEBUG_OPEN(">> pwc_isoc_cleanup()\n");
	if (pdev == NULL)
		return;
	if (pdev->iso_init == 0)
		return;

	pwc_iso_stop(pdev);
	pwc_iso_free(pdev);

	/* Stop camera, but only if we are sure the camera is still there (unplug
	   is signalled by EPIPE)
	 */
	if (pdev->error_status != EPIPE) {
		PWC_DEBUG_OPEN("Setting alternate interface 0.\n");
		usb_set_interface(pdev->udev, 0, 0);
	}

	pdev->iso_init = 0;
	PWC_DEBUG_OPEN("<< pwc_isoc_cleanup()\n");
}