#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  mach_msg_type_name_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  scalar_t__ ipc_object_t ;
typedef  TYPE_2__* ipc_kmsg_t ;
struct TYPE_5__ {TYPE_1__* ikm_header; } ;
struct TYPE_4__ {int msgh_bits; void* msgh_remote_port; void* msgh_local_port; } ;

/* Variables and functions */
 void* CAST_MACH_NAME_TO_PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAST_MACH_PORT_TO_NAME (scalar_t__) ; 
 int /*<<< orphan*/  IO_VALID (scalar_t__) ; 
 int MACH_MSGH_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_LOCAL (int) ; 
 int MACH_MSGH_BITS_OTHER (int) ; 
 int /*<<< orphan*/  MACH_MSGH_BITS_REMOTE (int) ; 
 int /*<<< orphan*/  MACH_PORT_DEAD ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ io_active (scalar_t__) ; 
 int /*<<< orphan*/  io_lock (scalar_t__) ; 
 int /*<<< orphan*/  io_release (scalar_t__) ; 
 int /*<<< orphan*/  io_unlock (scalar_t__) ; 
 int /*<<< orphan*/  ipc_object_copyout_dest (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ipc_kmsg_copyout_to_kernel(
	ipc_kmsg_t	kmsg,
	ipc_space_t	space)
{
	ipc_object_t dest;
	ipc_object_t reply;
	mach_msg_type_name_t dest_type;
	mach_msg_type_name_t reply_type;
	mach_port_name_t dest_name, reply_name;

	dest = (ipc_object_t) kmsg->ikm_header->msgh_remote_port;
	reply = (ipc_object_t) kmsg->ikm_header->msgh_local_port;
	dest_type = MACH_MSGH_BITS_REMOTE(kmsg->ikm_header->msgh_bits);
	reply_type = MACH_MSGH_BITS_LOCAL(kmsg->ikm_header->msgh_bits);

	assert(IO_VALID(dest));

	io_lock(dest);
	if (io_active(dest)) {
		ipc_object_copyout_dest(space, dest, dest_type, &dest_name);
		/* dest is unlocked */
	} else {
		io_unlock(dest);
		io_release(dest);
		dest_name = MACH_PORT_DEAD;
	}

	reply_name = CAST_MACH_PORT_TO_NAME(reply);

	kmsg->ikm_header->msgh_bits =
		(MACH_MSGH_BITS_OTHER(kmsg->ikm_header->msgh_bits) |
					MACH_MSGH_BITS(reply_type, dest_type));
	kmsg->ikm_header->msgh_local_port =  CAST_MACH_NAME_TO_PORT(dest_name);
	kmsg->ikm_header->msgh_remote_port = CAST_MACH_NAME_TO_PORT(reply_name);
}