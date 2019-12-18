#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
typedef  int /*<<< orphan*/  mach_msg_option_t ;
typedef  int /*<<< orphan*/  mach_msg_body_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
struct TYPE_7__ {TYPE_1__* ikm_header; } ;
struct TYPE_6__ {int msgh_bits; } ;

/* Variables and functions */
 int MACH_MSGH_BITS_COMPLEX ; 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 int /*<<< orphan*/  MACH_RCV_BODY_ERROR ; 
 int /*<<< orphan*/  ipc_kmsg_copyout_body (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_kmsg_copyout_header (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mach_msg_return_t
ipc_kmsg_copyout(
	ipc_kmsg_t		kmsg,
	ipc_space_t		space,
	vm_map_t		map,
	mach_msg_body_t		*slist,
	 mach_msg_option_t	option)
{
	mach_msg_return_t mr;

	mr = ipc_kmsg_copyout_header(kmsg, space, option);
	if (mr != MACH_MSG_SUCCESS) {
		return mr;
	}

	if (kmsg->ikm_header->msgh_bits & MACH_MSGH_BITS_COMPLEX) {
		mr = ipc_kmsg_copyout_body(kmsg, space, map, slist);

		if (mr != MACH_MSG_SUCCESS)
			mr |= MACH_RCV_BODY_ERROR;
	}

	return mr;
}