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
struct TYPE_5__ {scalar_t__ buffers; } ;
struct ivtv_stream {TYPE_2__ q_free; int /*<<< orphan*/  waitq; } ;
struct TYPE_6__ {TYPE_1__* events; } ;
struct ivtv_open_id {size_t type; TYPE_3__ fh; struct ivtv* itv; } ;
struct ivtv {int /*<<< orphan*/  i_flags; struct ivtv_stream* streams; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_4__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  subscribed; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_HI_FILE (char*) ; 
 int /*<<< orphan*/  IVTV_F_I_EV_DEC_STOPPED ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC ; 
 int /*<<< orphan*/  IVTV_F_I_EV_VSYNC_ENABLED ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ivtv_open_id* fh2id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_event_pending (TYPE_3__*) ; 

unsigned int ivtv_v4l2_dec_poll(struct file *filp, poll_table *wait)
{
	struct ivtv_open_id *id = fh2id(filp->private_data);
	struct ivtv *itv = id->itv;
	struct ivtv_stream *s = &itv->streams[id->type];
	int res = 0;

	/* add stream's waitq to the poll list */
	IVTV_DEBUG_HI_FILE("Decoder poll\n");

	/* If there are subscribed events, then only use the new event
	   API instead of the old video.h based API. */
	if (!list_empty(&id->fh.events->subscribed)) {
		poll_wait(filp, &id->fh.events->wait, wait);
		/* Turn off the old-style vsync events */
		clear_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);
		if (v4l2_event_pending(&id->fh))
			res = POLLPRI;
	} else {
		/* This is the old-style API which is here only for backwards
		   compatibility. */
		poll_wait(filp, &s->waitq, wait);
		set_bit(IVTV_F_I_EV_VSYNC_ENABLED, &itv->i_flags);
		if (test_bit(IVTV_F_I_EV_VSYNC, &itv->i_flags) ||
		    test_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags))
			res = POLLPRI;
	}

	/* Allow write if buffers are available for writing */
	if (s->q_free.buffers)
		res |= POLLOUT | POLLWRNORM;
	return res;
}