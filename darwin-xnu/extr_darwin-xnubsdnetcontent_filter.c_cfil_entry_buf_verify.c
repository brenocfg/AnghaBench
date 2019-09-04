#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ q_start; scalar_t__ q_end; } ;
struct cfe_buf {scalar_t__ cfe_peek_offset; scalar_t__ cfe_pass_offset; scalar_t__ cfe_peeked; TYPE_1__ cfe_ctl_q; TYPE_1__ cfe_pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFIL_QUEUE_VERIFY (TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static void
cfil_entry_buf_verify(struct cfe_buf *cfe_buf)
{
	CFIL_QUEUE_VERIFY(&cfe_buf->cfe_ctl_q);
	CFIL_QUEUE_VERIFY(&cfe_buf->cfe_pending_q);

	/* Verify the queues are ordered so that pending is before ctl */
	VERIFY(cfe_buf->cfe_ctl_q.q_start >= cfe_buf->cfe_pending_q.q_end);

	/* The peek offset cannot be less than the pass offset */
	VERIFY(cfe_buf->cfe_peek_offset >= cfe_buf->cfe_pass_offset);

	/* Make sure we've updated the offset we peeked at  */
	VERIFY(cfe_buf->cfe_ctl_q.q_start <= cfe_buf->cfe_peeked);
}