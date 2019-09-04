#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_port_name_t ;
typedef  scalar_t__ mach_msg_type_name_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
struct TYPE_9__ {scalar_t__ pad_end; int /*<<< orphan*/  type; scalar_t__ disposition; scalar_t__ name; } ;
typedef  TYPE_2__ mach_msg_port_descriptor_t ;
typedef  int mach_msg_option_t ;
struct TYPE_10__ {scalar_t__ disposition; scalar_t__ name; } ;
typedef  TYPE_3__ mach_msg_legacy_port_descriptor_t ;
typedef  int /*<<< orphan*/  mach_msg_descriptor_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  scalar_t__ ipc_port_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_4__* ipc_kmsg_t ;
struct TYPE_11__ {TYPE_1__* ikm_header; } ;
struct TYPE_8__ {int /*<<< orphan*/  msgh_bits; } ;

/* Variables and functions */
 scalar_t__ CAST_MACH_NAME_TO_PORT (scalar_t__) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_CIRCULAR ; 
 int /*<<< orphan*/  MACH_MSG_PORT_DESCRIPTOR ; 
 scalar_t__ MACH_MSG_TYPE_PORT_RECEIVE ; 
 scalar_t__ MACH_PORT_VALID (scalar_t__) ; 
 int /*<<< orphan*/  MACH_SEND_INVALID_RIGHT ; 
 int MACH_SEND_KERNEL ; 
 scalar_t__ ipc_object_copyin (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 scalar_t__ ipc_object_copyin_type (scalar_t__) ; 
 scalar_t__ ipc_port_check_circularity (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kGUARD_EXC_SEND_INVALID_RIGHT ; 
 int /*<<< orphan*/  mach_port_guard_exception (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mach_msg_descriptor_t *
ipc_kmsg_copyin_port_descriptor(
	volatile mach_msg_port_descriptor_t *dsc,
	mach_msg_legacy_port_descriptor_t *user_dsc_in,
	ipc_space_t space,
	ipc_object_t dest,
	ipc_kmsg_t kmsg,
	mach_msg_option_t *optionp,
	mach_msg_return_t *mr)
{
    volatile mach_msg_legacy_port_descriptor_t *user_dsc = user_dsc_in;
    mach_msg_type_name_t 	user_disp;
    mach_msg_type_name_t	result_disp;
    mach_port_name_t		name;
    ipc_object_t 			object;

    user_disp = user_dsc->disposition;
    result_disp = ipc_object_copyin_type(user_disp);

    name = (mach_port_name_t)user_dsc->name;
    if (MACH_PORT_VALID(name)) {

        kern_return_t kr = ipc_object_copyin(space, name, user_disp, &object);
        if (kr != KERN_SUCCESS) {
			if ((*optionp & MACH_SEND_KERNEL) == 0) {
				mach_port_guard_exception(name, 0, 0, kGUARD_EXC_SEND_INVALID_RIGHT);
			}
            *mr = MACH_SEND_INVALID_RIGHT;
            return NULL;
        }

        if ((result_disp == MACH_MSG_TYPE_PORT_RECEIVE) &&
                ipc_port_check_circularity((ipc_port_t) object,
                    (ipc_port_t) dest)) {
            kmsg->ikm_header->msgh_bits |= MACH_MSGH_BITS_CIRCULAR;
        }
        dsc->name = (ipc_port_t) object;
    } else {
        dsc->name = CAST_MACH_NAME_TO_PORT(name);
    }
    dsc->disposition = result_disp;
    dsc->type = MACH_MSG_PORT_DESCRIPTOR;

    dsc->pad_end = 0; // debug, unnecessary

    return (mach_msg_descriptor_t *)(user_dsc_in+1);
}