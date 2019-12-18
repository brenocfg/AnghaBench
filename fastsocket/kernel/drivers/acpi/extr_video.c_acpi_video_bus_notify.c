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
typedef  int u32 ;
struct input_dev {int dummy; } ;
struct acpi_video_bus {struct input_dev* input; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
#define  ACPI_VIDEO_NOTIFY_CYCLE 132 
#define  ACPI_VIDEO_NOTIFY_NEXT_OUTPUT 131 
#define  ACPI_VIDEO_NOTIFY_PREV_OUTPUT 130 
#define  ACPI_VIDEO_NOTIFY_PROBE 129 
#define  ACPI_VIDEO_NOTIFY_SWITCH 128 
 int KEY_SWITCHVIDEOMODE ; 
 int KEY_VIDEO_NEXT ; 
 int KEY_VIDEO_PREV ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (struct acpi_device*,int,int /*<<< orphan*/ ) ; 
 struct acpi_video_bus* acpi_driver_data (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_notifier_call_chain (struct acpi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_video_device_enumerate (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  acpi_video_device_rebind (struct acpi_video_bus*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void acpi_video_bus_notify(struct acpi_device *device, u32 event)
{
	struct acpi_video_bus *video = acpi_driver_data(device);
	struct input_dev *input;
	int keycode = 0;

	if (!video)
		return;

	input = video->input;

	switch (event) {
	case ACPI_VIDEO_NOTIFY_SWITCH:	/* User requested a switch,
					 * most likely via hotkey. */
		acpi_bus_generate_proc_event(device, event, 0);
		if (!acpi_notifier_call_chain(device, event, 0))
			keycode = KEY_SWITCHVIDEOMODE;
		break;

	case ACPI_VIDEO_NOTIFY_PROBE:	/* User plugged in or removed a video
					 * connector. */
		acpi_video_device_enumerate(video);
		acpi_video_device_rebind(video);
		acpi_bus_generate_proc_event(device, event, 0);
		keycode = KEY_SWITCHVIDEOMODE;
		break;

	case ACPI_VIDEO_NOTIFY_CYCLE:	/* Cycle Display output hotkey pressed. */
		acpi_bus_generate_proc_event(device, event, 0);
		keycode = KEY_SWITCHVIDEOMODE;
		break;
	case ACPI_VIDEO_NOTIFY_NEXT_OUTPUT:	/* Next Display output hotkey pressed. */
		acpi_bus_generate_proc_event(device, event, 0);
		keycode = KEY_VIDEO_NEXT;
		break;
	case ACPI_VIDEO_NOTIFY_PREV_OUTPUT:	/* previous Display output hotkey pressed. */
		acpi_bus_generate_proc_event(device, event, 0);
		keycode = KEY_VIDEO_PREV;
		break;

	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Unsupported event [0x%x]\n", event));
		break;
	}

	if (event != ACPI_VIDEO_NOTIFY_SWITCH)
		acpi_notifier_call_chain(device, event, 0);

	if (keycode) {
		input_report_key(input, keycode, 1);
		input_sync(input);
		input_report_key(input, keycode, 0);
		input_sync(input);
	}

	return;
}