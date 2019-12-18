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
struct pidff_device {int /*<<< orphan*/ * reports; int /*<<< orphan*/  hid; TYPE_4__* set_periodic; TYPE_1__* block_load; } ;
struct TYPE_7__ {int /*<<< orphan*/  period; int /*<<< orphan*/  phase; int /*<<< orphan*/  offset; int /*<<< orphan*/  magnitude; } ;
struct TYPE_8__ {TYPE_2__ periodic; } ;
struct ff_effect {TYPE_3__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 size_t PID_EFFECT_BLOCK_INDEX ; 
 size_t PID_MAGNITUDE ; 
 size_t PID_OFFSET ; 
 size_t PID_PERIOD ; 
 size_t PID_PHASE ; 
 size_t PID_SET_PERIODIC ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  pidff_set (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pidff_set_signed (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_submit_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pidff_set_periodic_report(struct pidff_device *pidff,
				      struct ff_effect *effect)
{
	pidff->set_periodic[PID_EFFECT_BLOCK_INDEX].value[0] =
		pidff->block_load[PID_EFFECT_BLOCK_INDEX].value[0];
	pidff_set_signed(&pidff->set_periodic[PID_MAGNITUDE],
			 effect->u.periodic.magnitude);
	pidff_set_signed(&pidff->set_periodic[PID_OFFSET],
			 effect->u.periodic.offset);
	pidff_set(&pidff->set_periodic[PID_PHASE], effect->u.periodic.phase);
	pidff->set_periodic[PID_PERIOD].value[0] = effect->u.periodic.period;

	usbhid_submit_report(pidff->hid, pidff->reports[PID_SET_PERIODIC],
			  USB_DIR_OUT);

}