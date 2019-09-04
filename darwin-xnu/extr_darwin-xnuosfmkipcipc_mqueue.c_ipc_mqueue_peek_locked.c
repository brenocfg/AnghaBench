#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ mach_port_seqno_t ;
typedef  int /*<<< orphan*/  mach_msg_size_t ;
typedef  int /*<<< orphan*/  mach_msg_max_trailer_t ;
typedef  int /*<<< orphan*/  mach_msg_id_t ;
typedef  TYPE_2__* ipc_mqueue_t ;
typedef  TYPE_3__* ipc_kmsg_t ;
typedef  int /*<<< orphan*/ * ipc_kmsg_queue_t ;
struct TYPE_13__ {TYPE_1__* ikm_header; } ;
struct TYPE_12__ {scalar_t__ imq_seqno; scalar_t__ imq_msgcount; int /*<<< orphan*/  imq_messages; } ;
struct TYPE_11__ {int /*<<< orphan*/  msgh_size; int /*<<< orphan*/  msgh_id; } ;

/* Variables and functions */
 TYPE_3__* IKM_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  imq_is_set (TYPE_2__*) ; 
 TYPE_3__* ipc_kmsg_queue_first (int /*<<< orphan*/ *) ; 
 TYPE_3__* ipc_kmsg_queue_next (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ round_msg (int /*<<< orphan*/ ) ; 

unsigned
ipc_mqueue_peek_locked(ipc_mqueue_t mq,
		       mach_port_seqno_t * seqnop,
		       mach_msg_size_t * msg_sizep,
		       mach_msg_id_t * msg_idp,
		       mach_msg_max_trailer_t * msg_trailerp,
		       ipc_kmsg_t *kmsgp)
{
	ipc_kmsg_queue_t kmsgq;
	ipc_kmsg_t kmsg;
	mach_port_seqno_t seqno, msgoff;
	unsigned res = 0;

	assert(!imq_is_set(mq));

	seqno = 0;
	if (seqnop != NULL)
		seqno = *seqnop;

	if (seqno == 0) {
		seqno = mq->imq_seqno;
		msgoff = 0;
	} else if (seqno >= mq->imq_seqno &&
		   seqno < mq->imq_seqno + mq->imq_msgcount) {
		msgoff = seqno - mq->imq_seqno;
	} else
		goto out;

	/* look for the message that would match that seqno */
	kmsgq = &mq->imq_messages;
	kmsg = ipc_kmsg_queue_first(kmsgq);
	while (msgoff-- && kmsg != IKM_NULL) {
		kmsg = ipc_kmsg_queue_next(kmsgq, kmsg);
	}
	if (kmsg == IKM_NULL)
		goto out;

	/* found one - return the requested info */
	if (seqnop != NULL)
		*seqnop = seqno;
	if (msg_sizep != NULL)
		*msg_sizep = kmsg->ikm_header->msgh_size;
	if (msg_idp != NULL)
		*msg_idp = kmsg->ikm_header->msgh_id;
	if (msg_trailerp != NULL)
		memcpy(msg_trailerp,
		       (mach_msg_max_trailer_t *)((vm_offset_t)kmsg->ikm_header +
						  round_msg(kmsg->ikm_header->msgh_size)),
		       sizeof(mach_msg_max_trailer_t));
	if (kmsgp != NULL)
		*kmsgp = kmsg;

	res = 1;

out:
	return res;
}