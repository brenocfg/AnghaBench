#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mrso_name; } ;
typedef  TYPE_1__ mach_right_send_once_t ;
typedef  int kern_return_t ;

/* Variables and functions */
 int KERN_FAILURE ; 
#define  KERN_INVALID_RIGHT 128 
 int /*<<< orphan*/  MACH_PORT_RIGHT_DEAD_NAME ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_SEND_ONCE ; 
 int /*<<< orphan*/  _mach_assert (char*,int) ; 
 int mach_port_mod_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self () ; 

void
mach_right_send_once_consume(mach_right_send_once_t so)
{
	kern_return_t kr = KERN_FAILURE;

	kr = mach_port_mod_refs(mach_task_self(), so.mrso_name,
			MACH_PORT_RIGHT_SEND_ONCE, -1);
	switch (kr) {
	case 0:
		break;
	case KERN_INVALID_RIGHT:
		kr = mach_port_mod_refs(mach_task_self(), so.mrso_name,
				MACH_PORT_RIGHT_DEAD_NAME, -1);
		_mach_assert("release dead name", kr);
		break;
	default:
		_mach_assert("consume send-once right", kr);
	}
}