#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pidff_device {int /*<<< orphan*/ * reports; int /*<<< orphan*/  hid; TYPE_4__* set_condition; TYPE_1__* block_load; } ;
struct TYPE_8__ {TYPE_2__* condition; } ;
struct ff_effect {TYPE_3__ u; } ;
struct TYPE_9__ {int* value; } ;
struct TYPE_7__ {int /*<<< orphan*/  deadband; int /*<<< orphan*/  left_saturation; int /*<<< orphan*/  right_saturation; int /*<<< orphan*/  left_coeff; int /*<<< orphan*/  right_coeff; int /*<<< orphan*/  center; } ;
struct TYPE_6__ {int* value; } ;

/* Variables and functions */
 size_t PID_CP_OFFSET ; 
 size_t PID_DEAD_BAND ; 
 size_t PID_EFFECT_BLOCK_INDEX ; 
 size_t PID_NEG_COEFFICIENT ; 
 size_t PID_NEG_SATURATION ; 
 size_t PID_PARAM_BLOCK_OFFSET ; 
 size_t PID_POS_COEFFICIENT ; 
 size_t PID_POS_SATURATION ; 
 size_t PID_SET_CONDITION ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  pidff_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pidff_set_signed (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_submit_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pidff_set_condition_report(struct pidff_device *pidff,
				       struct ff_effect *effect)
{
	int i;

	pidff->set_condition[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];

	for (i = 0; i < 2; i++) {
		pidff->set_condition[PID_PARAM_BLOCK_OFFSET].value[0] = i;
		pidff_set_signed(&pidff->set_condition[PID_CP_OFFSET],
				 effect->u.condition[i].center);
		pidff_set_signed(&pidff->set_condition[PID_POS_COEFFICIENT],
				 effect->u.condition[i].right_coeff);
		pidff_set_signed(&pidff->set_condition[PID_NEG_COEFFICIENT],
				 effect->u.condition[i].left_coeff);
		pidff_set(&pidff->set_condition[PID_POS_SATURATION],
			  effect->u.condition[i].right_saturation);
		pidff_set(&pidff->set_condition[PID_NEG_SATURATION],
			  effect->u.condition[i].left_saturation);
		pidff_set(&pidff->set_condition[PID_DEAD_BAND],
			  effect->u.condition[i].deadband);
		usbhid_submit_report(pidff->hid, pidff->reports[PID_SET_CONDITION],
				  USB_DIR_OUT);
	}
}