#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pidff_device {int /*<<< orphan*/ * reports; int /*<<< orphan*/  hid; TYPE_2__* effect_operation; int /*<<< orphan*/ * operation_id; TYPE_1__* effect_operation_status; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 size_t PID_EFFECT_BLOCK_INDEX ; 
 size_t PID_EFFECT_OPERATION ; 
 size_t PID_EFFECT_START ; 
 size_t PID_EFFECT_STOP ; 
 size_t PID_LOOP_COUNT ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  usbhid_submit_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pidff_playback_pid(struct pidff_device *pidff, int pid_id, int n)
{
	pidff->effect_operation[PID_EFFECT_BLOCK_INDEX].value[0] = pid_id;

	if (n == 0) {
		pidff->effect_operation_status->value[0] =
			pidff->operation_id[PID_EFFECT_STOP];
	} else {
		pidff->effect_operation_status->value[0] =
			pidff->operation_id[PID_EFFECT_START];
		pidff->effect_operation[PID_LOOP_COUNT].value[0] = n;
	}

	usbhid_submit_report(pidff->hid, pidff->reports[PID_EFFECT_OPERATION],
			  USB_DIR_OUT);
}