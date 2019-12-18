#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  scalar_t__ mach_msg_type_name_t ;
typedef  int /*<<< orphan*/  mach_msg_descriptor_t ;
struct TYPE_8__ {int /*<<< orphan*/  msgh_descriptor_count; } ;
typedef  TYPE_2__ mach_msg_body_t ;
typedef  int mach_msg_bits_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_3__* ipc_kmsg_t ;
struct TYPE_9__ {TYPE_1__* ikm_header; scalar_t__ ikm_voucher; } ;
struct TYPE_7__ {int msgh_bits; int /*<<< orphan*/  msgh_voucher_port; void* msgh_remote_port; void* msgh_local_port; } ;

/* Variables and functions */
 void* CAST_MACH_NAME_TO_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAST_MACH_PORT_TO_NAME (scalar_t__) ; 
 int IO_VALID (scalar_t__) ; 
 scalar_t__ IP_NULL ; 
 int MACH_MSGH_BITS_COMPLEX ; 
 scalar_t__ MACH_MSGH_BITS_LOCAL (int) ; 
 scalar_t__ MACH_MSGH_BITS_REMOTE (int) ; 
 int MACH_MSGH_BITS_SET (scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ MACH_MSGH_BITS_VOUCHER (int) ; 
 scalar_t__ MACH_MSG_TYPE_MOVE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ io_active (scalar_t__) ; 
 int /*<<< orphan*/  io_lock (scalar_t__) ; 
 int /*<<< orphan*/  io_release (scalar_t__) ; 
 int /*<<< orphan*/  io_unlock (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_assert_clean (TYPE_3__*) ; 
 int /*<<< orphan*/  ipc_kmsg_clean_body (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_object_copyout_dest (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_object_destroy (scalar_t__,scalar_t__) ; 

void
ipc_kmsg_copyout_dest(
	ipc_kmsg_t	kmsg,
	ipc_space_t	space)
{
	mach_msg_bits_t mbits;
	ipc_object_t dest;
	ipc_object_t reply;
	ipc_object_t voucher;
	mach_msg_type_name_t dest_type;
	mach_msg_type_name_t reply_type;
	mach_msg_type_name_t voucher_type;
	mach_port_name_t dest_name, reply_name, voucher_name;

	mbits = kmsg->ikm_header->msgh_bits;
	dest = (ipc_object_t) kmsg->ikm_header->msgh_remote_port;
	reply = (ipc_object_t) kmsg->ikm_header->msgh_local_port;
	voucher = (ipc_object_t) kmsg->ikm_voucher;
	voucher_name = kmsg->ikm_header->msgh_voucher_port;
	dest_type = MACH_MSGH_BITS_REMOTE(mbits);
	reply_type = MACH_MSGH_BITS_LOCAL(mbits);
	voucher_type = MACH_MSGH_BITS_VOUCHER(mbits);

	assert(IO_VALID(dest));

	ipc_importance_assert_clean(kmsg);

	io_lock(dest);
	if (io_active(dest)) {
		ipc_object_copyout_dest(space, dest, dest_type, &dest_name);
		/* dest is unlocked */
	} else {
		io_unlock(dest);
		io_release(dest);
		dest_name = MACH_PORT_DEAD;
	}

	if (IO_VALID(reply)) {
		ipc_object_destroy(reply, reply_type);
		reply_name = MACH_PORT_NULL;
	} else
		reply_name = CAST_MACH_PORT_TO_NAME(reply);

	if (IO_VALID(voucher)) {
		assert(voucher_type == MACH_MSG_TYPE_MOVE_SEND);

		kmsg->ikm_voucher = IP_NULL;
		ipc_object_destroy((ipc_object_t)voucher, voucher_type);
		voucher_name = MACH_PORT_NULL;
	}

	kmsg->ikm_header->msgh_bits = MACH_MSGH_BITS_SET(reply_type, dest_type,
							 voucher_type, mbits);
	kmsg->ikm_header->msgh_local_port = CAST_MACH_NAME_TO_PORT(dest_name);
	kmsg->ikm_header->msgh_remote_port = CAST_MACH_NAME_TO_PORT(reply_name);
	kmsg->ikm_header->msgh_voucher_port = voucher_name;

	if (mbits & MACH_MSGH_BITS_COMPLEX) {
		mach_msg_body_t *body;

		body = (mach_msg_body_t *) (kmsg->ikm_header + 1);
		ipc_kmsg_clean_body(kmsg, body->msgh_descriptor_count, 
				    (mach_msg_descriptor_t *)(body + 1));
	}
}