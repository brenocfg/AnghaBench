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
 int ACPI_VIDEO_BACKLIGHT ; 
 int ACPI_VIDEO_BACKLIGHT_DMI_VENDOR ; 
 int ACPI_VIDEO_BACKLIGHT_DMI_VIDEO ; 
 int ACPI_VIDEO_BACKLIGHT_FORCE_VENDOR ; 
 int ACPI_VIDEO_BACKLIGHT_FORCE_VIDEO ; 
 int /*<<< orphan*/  acpi_video_caps_checked ; 
 int /*<<< orphan*/  acpi_video_get_capabilities (int /*<<< orphan*/ *) ; 
 int acpi_video_support ; 

int acpi_video_backlight_support(void)
{
	/*
	 * We must check whether the ACPI graphics device is physically plugged
	 * in. Therefore this must be called after binding PCI and ACPI devices
	 */
	if (!acpi_video_caps_checked)
		acpi_video_get_capabilities(NULL);

	/* First check for boot param -> highest prio */
	if (acpi_video_support & ACPI_VIDEO_BACKLIGHT_FORCE_VENDOR)
		return 0;
	else if (acpi_video_support & ACPI_VIDEO_BACKLIGHT_FORCE_VIDEO)
		return 1;

	/* Then check for DMI blacklist -> second highest prio */
	if (acpi_video_support & ACPI_VIDEO_BACKLIGHT_DMI_VENDOR)
		return 0;
	else if (acpi_video_support & ACPI_VIDEO_BACKLIGHT_DMI_VIDEO)
		return 1;

	/* Then go the default way */
	return acpi_video_support & ACPI_VIDEO_BACKLIGHT;
}