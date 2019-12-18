#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pidff_device {int /*<<< orphan*/ * reports; int /*<<< orphan*/  hid; TYPE_4__* set_ramp; TYPE_1__* block_load; } ;
struct TYPE_6__ {int /*<<< orphan*/  end_level; int /*<<< orphan*/  start_level; } ;
struct TYPE_7__ {TYPE_2__ ramp; } ;
struct ff_effect {TYPE_3__ u; } ;
struct TYPE_8__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 size_t PID_EFFECT_BLOCK_INDEX ; 
 size_t PID_RAMP_END ; 
 size_t PID_RAMP_START ; 
 size_t PID_SET_RAMP ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  pidff_set_signed (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_submit_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pidff_set_ramp_force_report(struct pidff_device *pidff,
					struct ff_effect *effect)
{
	pidff->set_ramp[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];
	pidff_set_signed(&pidff->set_ramp[PID_RAMP_START],
			 effect->u.ramp.start_level);
	pidff_set_signed(&pidff->set_ramp[PID_RAMP_END],
			 effect->u.ramp.end_level);
	usbhid_submit_report(pidff->hid, pidff->reports[PID_SET_RAMP],
			  USB_DIR_OUT);
}