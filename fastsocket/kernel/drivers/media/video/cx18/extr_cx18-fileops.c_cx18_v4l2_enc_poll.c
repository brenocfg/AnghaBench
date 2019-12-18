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
struct file {struct cx18_open_id* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  depth; } ;
struct cx18_stream {TYPE_1__ q_full; int /*<<< orphan*/  waitq; int /*<<< orphan*/  name; int /*<<< orphan*/  s_flags; } ;
struct cx18_open_id {size_t type; struct cx18* cx; } ;
struct cx18 {int /*<<< orphan*/  serialize_lock; struct cx18_stream* streams; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_FILE (char*) ; 
 int /*<<< orphan*/  CX18_DEBUG_HI_FILE (char*) ; 
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CX18_F_S_STREAMING ; 
 int /*<<< orphan*/  CX18_F_S_STREAMOFF ; 
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cx18_start_capture (struct cx18_open_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned int cx18_v4l2_enc_poll(struct file *filp, poll_table *wait)
{
	struct cx18_open_id *id = filp->private_data;
	struct cx18 *cx = id->cx;
	struct cx18_stream *s = &cx->streams[id->type];
	int eof = test_bit(CX18_F_S_STREAMOFF, &s->s_flags);

	/* Start a capture if there is none */
	if (!eof && !test_bit(CX18_F_S_STREAMING, &s->s_flags)) {
		int rc;

		mutex_lock(&cx->serialize_lock);
		rc = cx18_start_capture(id);
		mutex_unlock(&cx->serialize_lock);
		if (rc) {
			CX18_DEBUG_INFO("Could not start capture for %s (%d)\n",
					s->name, rc);
			return POLLERR;
		}
		CX18_DEBUG_FILE("Encoder poll started capture\n");
	}

	/* add stream's waitq to the poll list */
	CX18_DEBUG_HI_FILE("Encoder poll\n");
	poll_wait(filp, &s->waitq, wait);

	if (atomic_read(&s->q_full.depth))
		return POLLIN | POLLRDNORM;
	if (eof)
		return POLLHUP;
	return 0;
}