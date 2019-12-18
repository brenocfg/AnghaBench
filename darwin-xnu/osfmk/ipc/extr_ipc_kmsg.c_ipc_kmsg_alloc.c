#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_ool_descriptor32_t ;
typedef  int /*<<< orphan*/  mach_msg_base_t ;
typedef  scalar_t__ ipc_kmsg_t ;

/* Variables and functions */
 int DESC_SIZE_ADJUSTMENT ; 
 scalar_t__ IKM_NULL ; 
 int IKM_SAVED_MSG_SIZE ; 
 int MACH_MSG_SIZE_MAX ; 
 int MAX_TRAILER_SIZE ; 
 int /*<<< orphan*/  ikm_init (scalar_t__,int) ; 
 int /*<<< orphan*/  ikm_plus_overhead (int) ; 
 int /*<<< orphan*/  ikm_set_header (scalar_t__,int) ; 
 int ipc_kmsg_max_body_space ; 
 int /*<<< orphan*/  ipc_kmsg_zone ; 
 scalar_t__ kalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

ipc_kmsg_t
ipc_kmsg_alloc(
	mach_msg_size_t msg_and_trailer_size)
{
	mach_msg_size_t max_expanded_size;
	ipc_kmsg_t kmsg;

	/*
	 * LP64support -
	 * Pad the allocation in case we need to expand the
	 * message descrptors for user spaces with pointers larger than
	 * the kernel's own, or vice versa.  We don't know how many descriptors
	 * there are yet, so just assume the whole body could be
	 * descriptors (if there could be any at all).
	 *
	 * The expansion space is left in front of the header,
	 * because it is easier to pull the header and descriptors
	 * forward as we process them than it is to push all the
	 * data backwards.
	 */
	mach_msg_size_t size = msg_and_trailer_size - MAX_TRAILER_SIZE;

	/* compare against implementation upper limit for the body */
	if (size > ipc_kmsg_max_body_space)
		return IKM_NULL;

	if (size > sizeof(mach_msg_base_t)) {
		mach_msg_size_t max_desc = (mach_msg_size_t)(((size - sizeof(mach_msg_base_t)) /
				           sizeof(mach_msg_ool_descriptor32_t)) *
				           DESC_SIZE_ADJUSTMENT);

		/* make sure expansion won't cause wrap */
		if (msg_and_trailer_size > MACH_MSG_SIZE_MAX - max_desc)
			return IKM_NULL;

		max_expanded_size = msg_and_trailer_size + max_desc;
	} else
	  max_expanded_size = msg_and_trailer_size;

	if (max_expanded_size < IKM_SAVED_MSG_SIZE)
		max_expanded_size = IKM_SAVED_MSG_SIZE; 	/* round up for ikm_cache */

	if (max_expanded_size == IKM_SAVED_MSG_SIZE) {
		kmsg = (ipc_kmsg_t)zalloc(ipc_kmsg_zone);
	} else {
		kmsg = (ipc_kmsg_t)kalloc(ikm_plus_overhead(max_expanded_size));
	}

	if (kmsg != IKM_NULL) {
		ikm_init(kmsg, max_expanded_size);
		ikm_set_header(kmsg, msg_and_trailer_size);
	}

	return(kmsg);
}