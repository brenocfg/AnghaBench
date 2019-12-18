#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  depth; } ;
struct TYPE_6__ {int /*<<< orphan*/  depth; } ;
struct TYPE_4__ {int /*<<< orphan*/  depth; } ;
struct cx18_stream {TYPE_2__ q_free; TYPE_3__ q_full; TYPE_1__ q_busy; } ;
struct cx18_mdl {int dummy; } ;
struct cx18 {struct cx18_stream* streams; } ;

/* Variables and functions */
 size_t CX18_ENC_STREAM_TYPE_IDX ; 
 scalar_t__ CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct cx18_mdl* cx18_dequeue (struct cx18_stream*,TYPE_3__*) ; 
 int /*<<< orphan*/  cx18_enqueue (struct cx18_stream*,struct cx18_mdl*,TYPE_2__*) ; 
 int /*<<< orphan*/  cx18_stream_enabled (struct cx18_stream*) ; 

void cx18_stream_rotate_idx_mdls(struct cx18 *cx)
{
	struct cx18_stream *s = &cx->streams[CX18_ENC_STREAM_TYPE_IDX];
	struct cx18_mdl *mdl;

	if (!cx18_stream_enabled(s))
		return;

	/* Return if the firmware is not running low on MDLs */
	if ((atomic_read(&s->q_free.depth) + atomic_read(&s->q_busy.depth)) >=
					    CX18_ENC_STREAM_TYPE_IDX_FW_MDL_MIN)
		return;

	/* Return if there are no MDLs to rotate back to the firmware */
	if (atomic_read(&s->q_full.depth) < 2)
		return;

	/*
	 * Take the oldest IDX MDL still holding data, and discard its index
	 * entries by scheduling the MDL to go back to the firmware
	 */
	mdl = cx18_dequeue(s, &s->q_full);
	if (mdl != NULL)
		cx18_enqueue(s, mdl, &s->q_free);
}