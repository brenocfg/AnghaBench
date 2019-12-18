#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_msg_type_name_t ;
typedef  int mach_msg_return_t ;
typedef  int /*<<< orphan*/  mach_msg_body_t ;
typedef  int mach_msg_bits_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  int /*<<< orphan*/  ipc_object_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
struct TYPE_10__ {int /*<<< orphan*/  ith_knote; } ;
struct TYPE_9__ {TYPE_1__* ikm_header; int /*<<< orphan*/  ikm_voucher; } ;
struct TYPE_8__ {int msgh_bits; int /*<<< orphan*/  msgh_voucher_port; void* msgh_local_port; void* msgh_remote_port; } ;

/* Variables and functions */
 void* CAST_MACH_NAME_TO_PORT (int /*<<< orphan*/ ) ; 
 int IO_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_NULL ; 
 int /*<<< orphan*/  ITH_KNOTE_PSEUDO ; 
 int MACH_MSGH_BITS_COMPLEX ; 
 scalar_t__ MACH_MSGH_BITS_LOCAL (int) ; 
 scalar_t__ MACH_MSGH_BITS_REMOTE (int) ; 
 int MACH_MSGH_BITS_USER ; 
 scalar_t__ MACH_MSGH_BITS_VOUCHER (int) ; 
 scalar_t__ MACH_MSG_TYPE_MOVE_SEND ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* current_thread () ; 
 int /*<<< orphan*/  ipc_importance_assert_clean (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_clean (TYPE_2__*) ; 
 int ipc_kmsg_copyout_body (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ipc_kmsg_copyout_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

mach_msg_return_t
ipc_kmsg_copyout_pseudo(
	ipc_kmsg_t		kmsg,
	ipc_space_t		space,
	vm_map_t		map,
	mach_msg_body_t		*slist)
{
	mach_msg_bits_t mbits = kmsg->ikm_header->msgh_bits;
	ipc_object_t dest = (ipc_object_t) kmsg->ikm_header->msgh_remote_port;
	ipc_object_t reply = (ipc_object_t) kmsg->ikm_header->msgh_local_port;
	ipc_object_t voucher = (ipc_object_t) kmsg->ikm_voucher;
	mach_msg_type_name_t dest_type = MACH_MSGH_BITS_REMOTE(mbits);
	mach_msg_type_name_t reply_type = MACH_MSGH_BITS_LOCAL(mbits);
	mach_msg_type_name_t voucher_type = MACH_MSGH_BITS_VOUCHER(mbits);
	mach_port_name_t voucher_name = kmsg->ikm_header->msgh_voucher_port;
	mach_port_name_t dest_name, reply_name;
	mach_msg_return_t mr;

	/* Set ith_knote to ITH_KNOTE_PSEUDO */
	current_thread()->ith_knote = ITH_KNOTE_PSEUDO;

	assert(IO_VALID(dest));

#if 0
	/*
	 * If we did this here, it looks like we wouldn't need the undo logic
	 * at the end of ipc_kmsg_send() in the error cases.  Not sure which
	 * would be more elegant to keep.
	 */
	ipc_importance_clean(kmsg);
#else
	/* just assert it is already clean */
	ipc_importance_assert_clean(kmsg);
#endif

	mr = (ipc_kmsg_copyout_object(space, dest, dest_type, &dest_name) |
	      ipc_kmsg_copyout_object(space, reply, reply_type, &reply_name));

	kmsg->ikm_header->msgh_bits = mbits & MACH_MSGH_BITS_USER;
	kmsg->ikm_header->msgh_remote_port = CAST_MACH_NAME_TO_PORT(dest_name);
	kmsg->ikm_header->msgh_local_port = CAST_MACH_NAME_TO_PORT(reply_name);

	if (IO_VALID(voucher)) {
		assert(voucher_type == MACH_MSG_TYPE_MOVE_SEND);

		kmsg->ikm_voucher = IP_NULL;
		mr |= ipc_kmsg_copyout_object(space, voucher, voucher_type, &voucher_name);
		kmsg->ikm_header->msgh_voucher_port = voucher_name;
	}
		
	if (mbits & MACH_MSGH_BITS_COMPLEX) {
		mr |= ipc_kmsg_copyout_body(kmsg, space, map, slist);
	}

	return mr;
}