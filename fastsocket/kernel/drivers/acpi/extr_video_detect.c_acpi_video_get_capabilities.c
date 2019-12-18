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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  acpi_bus_get_device (int /*<<< orphan*/ *,struct acpi_device**) ; 
 char* acpi_device_bid (struct acpi_device*) ; 
 int acpi_video_caps_checked ; 
 long acpi_video_support ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_video ; 

long acpi_video_get_capabilities(acpi_handle graphics_handle)
{
	long caps = 0;
	struct acpi_device *tmp_dev;
	acpi_status status;

	if (acpi_video_caps_checked && graphics_handle == NULL)
		return acpi_video_support;

	if (!graphics_handle) {
		/* Only do the global walk through all graphics devices once */
		acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				    ACPI_UINT32_MAX, find_video,
				    &caps, NULL);
		/* There might be boot param flags set already... */
		acpi_video_support |= caps;
		acpi_video_caps_checked = 1;
		/* Add blacklists here. Be careful to use the right *DMI* bits
		 * to still be able to override logic via boot params, e.g.:
		 *
		 *   if (dmi_name_in_vendors("XY")) {
		 *	acpi_video_support |=
		 *		ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VENDOR;
		 *	acpi_video_support |=
		 *		ACPI_VIDEO_BACKLIGHT_DMI_VENDOR;
		 *}
		 */
	} else {
		status = acpi_bus_get_device(graphics_handle, &tmp_dev);
		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status, "Invalid device"));
			return 0;
		}
		acpi_walk_namespace(ACPI_TYPE_DEVICE, graphics_handle,
				    ACPI_UINT32_MAX, find_video,
				    &caps, NULL);
	}
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "We have 0x%lX video support %s %s\n",
			  graphics_handle ? caps : acpi_video_support,
			  graphics_handle ? "on device " : "in general",
			  graphics_handle ? acpi_device_bid(tmp_dev) : ""));
	return caps;
}