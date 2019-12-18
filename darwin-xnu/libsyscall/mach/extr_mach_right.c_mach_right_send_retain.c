#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mrs_name; } ;
typedef  TYPE_1__ mach_right_send_t ;
typedef  int kern_return_t ;

/* Variables and functions */
 int KERN_FAILURE ; 
#define  KERN_INVALID_NAME 129 
#define  KERN_INVALID_RIGHT 128 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_SEND ; 
 TYPE_1__ MACH_RIGHT_SEND_NULL ; 
 int /*<<< orphan*/  _mach_assert (char*,int) ; 
 int mach_port_mod_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mach_task_self () ; 

mach_right_send_t
mach_right_send_retain(mach_right_send_t s)
{
	kern_return_t kr = KERN_FAILURE;
	mach_right_send_t rs = MACH_RIGHT_SEND_NULL;

	kr = mach_port_mod_refs(mach_task_self(), s.mrs_name,
			MACH_PORT_RIGHT_SEND, 1);
	switch (kr) {
	case 0:
		rs = s;
		break;
	case KERN_INVALID_RIGHT:
		rs.mrs_name = MACH_PORT_DEAD;
		break;
	case KERN_INVALID_NAME:
		// mach_port_mod_refs() will return success when given either
		// MACH_PORT_DEAD or MACH_PORT_NULL with send or send-once right
		// operations, so this is always fatal.
	default:
		_mach_assert("retain send right", kr);
	}

	return rs;
}