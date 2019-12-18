#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int length; } ;
struct TYPE_9__ {TYPE_3__ header; } ;
struct TYPE_7__ {int length; } ;
struct TYPE_10__ {TYPE_4__ mdb; TYPE_2__ header; } ;
struct TYPE_6__ {scalar_t__ length; } ;
struct write_sccb {TYPE_5__ msg_buf; TYPE_1__ header; } ;
struct sclp_buffer {int current_length; int mto_char_sum; int /*<<< orphan*/  mto_number; struct write_sccb* sccb; int /*<<< orphan*/ * current_line; } ;
struct mto {int length; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */

__attribute__((used)) static void
sclp_finalize_mto(struct sclp_buffer *buffer)
{
	struct write_sccb *sccb;
	struct mto *mto;
	int str_len, mto_size;

	str_len = buffer->current_length;
	buffer->current_line = NULL;
	buffer->current_length = 0;

	/* real size of new Message Text Object including message text	*/
	mto_size = sizeof(struct mto) + str_len;

	/* find address of new message text object */
	sccb = buffer->sccb;
	mto = (struct mto *)(((addr_t) sccb) + sccb->header.length);

	/* set size of message text object */
	mto->length = mto_size;

	/*
	 * update values of sizes
	 * (SCCB, Event(Message) Buffer, Message Data Block)
	 */
	sccb->header.length += mto_size;
	sccb->msg_buf.header.length += mto_size;
	sccb->msg_buf.mdb.header.length += mto_size;

	/*
	 * count number of buffered messages (= number of Message Text
	 * Objects) and number of buffered characters
	 * for the SCCB currently used for buffering and at all
	 */
	buffer->mto_number++;
	buffer->mto_char_sum += str_len;
}