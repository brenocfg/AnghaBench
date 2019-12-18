#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct cx18_stream {int type; int buf_size; int bufs_per_mdl; int mdl_size; int id; int /*<<< orphan*/  out_work_order; TYPE_2__ q_idle; TYPE_2__ q_full; TYPE_2__ q_busy; TYPE_2__ q_free; int /*<<< orphan*/  waitq; int /*<<< orphan*/  buf_pool; int /*<<< orphan*/  buffers; int /*<<< orphan*/  dma; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; struct cx18* cx; int /*<<< orphan*/ * dvb; struct video_device* video_dev; } ;
struct cx18 {int* stream_buf_size; int /*<<< orphan*/ * stream_buffers; struct cx18_stream* streams; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_INVALID_TASK_HANDLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_out_work_handler ; 
 int /*<<< orphan*/  cx18_queue_init (TYPE_2__*) ; 
 TYPE_1__* cx18_stream_info ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cx18_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx18_stream_init(struct cx18 *cx, int type)
{
	struct cx18_stream *s = &cx->streams[type];
	struct video_device *video_dev = s->video_dev;

	/* we need to keep video_dev, so restore it afterwards */
	memset(s, 0, sizeof(*s));
	s->video_dev = video_dev;

	/* initialize cx18_stream fields */
	s->dvb = NULL;
	s->cx = cx;
	s->type = type;
	s->name = cx18_stream_info[type].name;
	s->handle = CX18_INVALID_TASK_HANDLE;

	s->dma = cx18_stream_info[type].dma;
	s->buffers = cx->stream_buffers[type];
	s->buf_size = cx->stream_buf_size[type];
	INIT_LIST_HEAD(&s->buf_pool);
	s->bufs_per_mdl = 1;
	s->mdl_size = s->buf_size * s->bufs_per_mdl;

	init_waitqueue_head(&s->waitq);
	s->id = -1;
	spin_lock_init(&s->q_free.lock);
	cx18_queue_init(&s->q_free);
	spin_lock_init(&s->q_busy.lock);
	cx18_queue_init(&s->q_busy);
	spin_lock_init(&s->q_full.lock);
	cx18_queue_init(&s->q_full);
	spin_lock_init(&s->q_idle.lock);
	cx18_queue_init(&s->q_idle);

	INIT_WORK(&s->out_work_order, cx18_out_work_handler);
}