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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_msg_descriptor_t ;
typedef  int /*<<< orphan*/  mach_msg_bits_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
struct TYPE_7__ {scalar_t__ ikm_voucher; TYPE_1__* ikm_header; } ;
struct TYPE_6__ {scalar_t__ msgh_local_port; scalar_t__ msgh_remote_port; int /*<<< orphan*/  msgh_bits; } ;

/* Variables and functions */
 int IO_VALID (scalar_t__) ; 
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_LOCAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_REMOTE (int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_MSGH_BITS_VOUCHER (int /*<<< orphan*/ ) ; 
 scalar_t__ MACH_MSG_TYPE_MOVE_SEND ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_PORT_SEND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_importance_clean (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_kernel_copy_map ; 
 int /*<<< orphan*/  ipc_kmsg_clean_body (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipc_object_destroy (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_object_destroy_dest (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_deallocate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
ipc_kmsg_clean_partial(
	ipc_kmsg_t		kmsg,
	mach_msg_type_number_t	number,
	mach_msg_descriptor_t	*desc,
	vm_offset_t		paddr,
	vm_size_t		length)
{
	ipc_object_t object;
	mach_msg_bits_t mbits = kmsg->ikm_header->msgh_bits;

	/* deal with importance chain while we still have dest and voucher references */
	ipc_importance_clean(kmsg);

	object = (ipc_object_t) kmsg->ikm_header->msgh_remote_port;
	assert(IO_VALID(object));
	ipc_object_destroy_dest(object, MACH_MSGH_BITS_REMOTE(mbits));

	object = (ipc_object_t) kmsg->ikm_header->msgh_local_port;
	if (IO_VALID(object))
		ipc_object_destroy(object, MACH_MSGH_BITS_LOCAL(mbits));

	object = (ipc_object_t) kmsg->ikm_voucher;
	if (IO_VALID(object)) {
		assert(MACH_MSGH_BITS_VOUCHER(mbits) == MACH_MSG_TYPE_MOVE_SEND);
		ipc_object_destroy(object, MACH_MSG_TYPE_PORT_SEND);
		kmsg->ikm_voucher = IP_NULL;
	}

	if (paddr) {
		(void) vm_deallocate(ipc_kernel_copy_map, paddr, length);
	}

	ipc_kmsg_clean_body(kmsg, number, desc);
}