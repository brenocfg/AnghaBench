#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ header; } ;
struct write_sccb {TYPE_2__ msg_buf; } ;
struct TYPE_8__ {struct write_sccb* sccb; struct sclp_buffer* callback_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;
struct sclp_buffer {scalar_t__ mto_number; void (* callback ) (struct sclp_buffer*,int) ;TYPE_4__ request; struct write_sccb* sccb; int /*<<< orphan*/ * current_line; } ;
struct TYPE_7__ {int sclp_receive_mask; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSYS ; 
 int /*<<< orphan*/  EVTYP_MSG ; 
 int EVTYP_MSG_MASK ; 
 int /*<<< orphan*/  EVTYP_PMSGCMD ; 
 int EVTYP_PMSGCMD_MASK ; 
 int /*<<< orphan*/  SCLP_CMDW_WRITE_EVENT_DATA ; 
 int /*<<< orphan*/  SCLP_REQ_FILLED ; 
 int sclp_add_request (TYPE_4__*) ; 
 int /*<<< orphan*/  sclp_finalize_mto (struct sclp_buffer*) ; 
 TYPE_3__ sclp_rw_event ; 
 int /*<<< orphan*/  sclp_writedata_callback ; 

int
sclp_emit_buffer(struct sclp_buffer *buffer,
		 void (*callback)(struct sclp_buffer *, int))
{
	struct write_sccb *sccb;

	/* add current line if there is one */
	if (buffer->current_line != NULL)
		sclp_finalize_mto(buffer);

	/* Are there messages in the output buffer ? */
	if (buffer->mto_number == 0)
		return -EIO;

	sccb = buffer->sccb;
	if (sclp_rw_event.sclp_receive_mask & EVTYP_MSG_MASK)
		/* Use normal write message */
		sccb->msg_buf.header.type = EVTYP_MSG;
	else if (sclp_rw_event.sclp_receive_mask & EVTYP_PMSGCMD_MASK)
		/* Use write priority message */
		sccb->msg_buf.header.type = EVTYP_PMSGCMD;
	else
		return -ENOSYS;
	buffer->request.command = SCLP_CMDW_WRITE_EVENT_DATA;
	buffer->request.status = SCLP_REQ_FILLED;
	buffer->request.callback = sclp_writedata_callback;
	buffer->request.callback_data = buffer;
	buffer->request.sccb = sccb;
	buffer->callback = callback;
	return sclp_add_request(&buffer->request);
}