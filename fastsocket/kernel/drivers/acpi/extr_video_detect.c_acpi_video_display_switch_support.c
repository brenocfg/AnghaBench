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
 int ACPI_VIDEO_OUTPUT_SWITCHING ; 
 int ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VENDOR ; 
 int ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VIDEO ; 
 int ACPI_VIDEO_OUTPUT_SWITCHING_FORCE_VENDOR ; 
 int ACPI_VIDEO_OUTPUT_SWITCHING_FORCE_VIDEO ; 
 int /*<<< orphan*/  acpi_video_caps_checked ; 
 int /*<<< orphan*/  acpi_video_get_capabilities (int /*<<< orphan*/ *) ; 
 int acpi_video_support ; 

int acpi_video_display_switch_support(void)
{
	if (!acpi_video_caps_checked)
		acpi_video_get_capabilities(NULL);

	if (acpi_video_support & ACPI_VIDEO_OUTPUT_SWITCHING_FORCE_VENDOR)
		return 0;
	else if (acpi_video_support & ACPI_VIDEO_OUTPUT_SWITCHING_FORCE_VIDEO)
		return 1;

	if (acpi_video_support & ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VENDOR)
		return 0;
	else if (acpi_video_support & ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VIDEO)
		return 1;

	return acpi_video_support & ACPI_VIDEO_OUTPUT_SWITCHING;
}