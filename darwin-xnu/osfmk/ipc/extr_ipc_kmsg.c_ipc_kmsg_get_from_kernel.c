#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_return_t ;
struct TYPE_25__ {scalar_t__ sender; } ;
struct TYPE_26__ {TYPE_3__ msgh_labels; int /*<<< orphan*/  msgh_trailer_size; int /*<<< orphan*/  msgh_trailer_type; int /*<<< orphan*/  msgh_audit; int /*<<< orphan*/  msgh_sender; } ;
typedef  TYPE_4__ mach_msg_max_trailer_t ;
struct TYPE_27__ {int msgh_bits; scalar_t__ msgh_remote_port; } ;
typedef  TYPE_5__ mach_msg_header_t ;
struct TYPE_23__ {int msgh_descriptor_count; } ;
struct TYPE_28__ {TYPE_1__ body; } ;
typedef  TYPE_6__ mach_msg_base_t ;
typedef  TYPE_7__* ipc_port_t ;
typedef  TYPE_8__* ipc_kmsg_t ;
struct TYPE_30__ {int ikm_size; TYPE_2__* ikm_header; } ;
struct TYPE_29__ {TYPE_8__* ip_premsg; } ;
struct TYPE_24__ {int msgh_size; } ;

/* Variables and functions */
 int DESC_SIZE_ADJUSTMENT ; 
 TYPE_8__* IKM_NULL ; 
 int IP_PREALLOC (TYPE_7__*) ; 
 scalar_t__ IP_VALID (TYPE_7__*) ; 
 int /*<<< orphan*/  KERNEL_AUDIT_TOKEN ; 
 int /*<<< orphan*/  KERNEL_SECURITY_TOKEN ; 
 int MACH_MSGH_BITS_COMPLEX ; 
 int /*<<< orphan*/  MACH_MSG_SUCCESS ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_FORMAT_0 ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_MINIMUM_SIZE ; 
 int /*<<< orphan*/  MACH_SEND_NO_BUFFER ; 
 int /*<<< orphan*/  MACH_SEND_TOO_LARGE ; 
 int MAX_TRAILER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ikm_prealloc_inuse (TYPE_8__*) ; 
 int /*<<< orphan*/  ikm_prealloc_set_inuse (TYPE_8__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ikm_qos_init (TYPE_8__*) ; 
 int /*<<< orphan*/  ikm_set_header (TYPE_8__*,int) ; 
 int /*<<< orphan*/  ip_active (TYPE_7__*) ; 
 int /*<<< orphan*/  ip_lock (TYPE_7__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_7__*) ; 
 TYPE_8__* ipc_kmsg_alloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int) ; 

mach_msg_return_t
ipc_kmsg_get_from_kernel(
	mach_msg_header_t	*msg,
	mach_msg_size_t	size,
	ipc_kmsg_t		*kmsgp)
{
	ipc_kmsg_t 	kmsg;
	mach_msg_size_t	msg_and_trailer_size;
	mach_msg_max_trailer_t *trailer;
	ipc_port_t	dest_port;

	assert(size >= sizeof(mach_msg_header_t));
	assert((size & 3) == 0);

	dest_port = (ipc_port_t)msg->msgh_remote_port;

	msg_and_trailer_size = size + MAX_TRAILER_SIZE;

	/*
	 * See if the port has a pre-allocated kmsg for kernel
	 * clients.  These are set up for those kernel clients
	 * which cannot afford to wait.
	 */
	if (IP_VALID(dest_port) && IP_PREALLOC(dest_port)) {
		mach_msg_size_t max_desc = 0;

		ip_lock(dest_port);
		if (!ip_active(dest_port)) {
			ip_unlock(dest_port);
			return MACH_SEND_NO_BUFFER;
		}
		assert(IP_PREALLOC(dest_port));
		kmsg = dest_port->ip_premsg;
		if (ikm_prealloc_inuse(kmsg)) {
			ip_unlock(dest_port);
			return MACH_SEND_NO_BUFFER;
		}
#if !defined(__LP64__)
		if (msg->msgh_bits & MACH_MSGH_BITS_COMPLEX) {
			assert(size > sizeof(mach_msg_base_t));
			max_desc = ((mach_msg_base_t *)msg)->body.msgh_descriptor_count *
				DESC_SIZE_ADJUSTMENT;
		}
#endif
		if (msg_and_trailer_size > kmsg->ikm_size - max_desc) {
			ip_unlock(dest_port);
			return MACH_SEND_TOO_LARGE;
		}
		ikm_prealloc_set_inuse(kmsg, dest_port);
		ikm_set_header(kmsg, msg_and_trailer_size);
		ip_unlock(dest_port);
	}
	else
	{
		kmsg = ipc_kmsg_alloc(msg_and_trailer_size);
		if (kmsg == IKM_NULL)
			return MACH_SEND_NO_BUFFER;
	}

	(void) memcpy((void *) kmsg->ikm_header, (const void *) msg, size);

	ikm_qos_init(kmsg);

	kmsg->ikm_header->msgh_size = size;

	/* 
	 * I reserve for the trailer the largest space (MAX_TRAILER_SIZE)
	 * However, the internal size field of the trailer (msgh_trailer_size)
	 * is initialized to the minimum (sizeof(mach_msg_trailer_t)), to
	 * optimize the cases where no implicit data is requested.
	 */
	trailer = (mach_msg_max_trailer_t *) 
	          ((vm_offset_t)kmsg->ikm_header + size);
	trailer->msgh_sender = KERNEL_SECURITY_TOKEN;
	trailer->msgh_audit = KERNEL_AUDIT_TOKEN;
	trailer->msgh_trailer_type = MACH_MSG_TRAILER_FORMAT_0;
	trailer->msgh_trailer_size = MACH_MSG_TRAILER_MINIMUM_SIZE;

	trailer->msgh_labels.sender = 0;

	*kmsgp = kmsg;
	return MACH_MSG_SUCCESS;
}