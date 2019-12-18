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
struct videobuf_queue {scalar_t__ type; scalar_t__ inputs; int /*<<< orphan*/  wait; int /*<<< orphan*/  irqlock; TYPE_3__* ops; scalar_t__ streaming; int /*<<< orphan*/  stream; struct videobuf_buffer** bufs; scalar_t__ reading; TYPE_1__* int_ops; } ;
struct videobuf_buffer {int memory; scalar_t__ state; scalar_t__ input; int /*<<< orphan*/  stream; int /*<<< orphan*/  boff; int /*<<< orphan*/  baddr; int /*<<< orphan*/  bsize; int /*<<< orphan*/  ts; int /*<<< orphan*/  field; int /*<<< orphan*/  size; int /*<<< orphan*/  magic; } ;
struct TYPE_7__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  userptr; } ;
struct v4l2_buffer {int memory; scalar_t__ type; size_t index; int flags; scalar_t__ input; TYPE_2__ m; int /*<<< orphan*/  length; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  bytesused; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_10__ {TYPE_4__* mm; } ;
struct TYPE_9__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_8__ {int (* buf_prepare ) (struct videobuf_queue*,struct videobuf_buffer*,int) ;int /*<<< orphan*/  (* buf_queue ) (struct videobuf_queue*,struct videobuf_buffer*) ;int /*<<< orphan*/  (* buf_release ) (struct videobuf_queue*,struct videobuf_buffer*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAGIC_BUFFER ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_QTYPE_OPS ; 
 scalar_t__ UNSET ; 
 int V4L2_BUF_FLAG_INPUT ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_OUTPUT ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_OUTPUT ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_MEMORY_MMAP 130 
#define  V4L2_MEMORY_OVERLAY 129 
#define  V4L2_MEMORY_USERPTR 128 
 scalar_t__ VIDEOBUF_IDLE ; 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 size_t VIDEO_MAX_FRAME ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct videobuf_queue*,struct videobuf_buffer*) ; 
 int stub2 (struct videobuf_queue*,struct videobuf_buffer*,int) ; 
 int /*<<< orphan*/  stub3 (struct videobuf_queue*,struct videobuf_buffer*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int videobuf_next_field (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  wake_up_interruptible_sync (int /*<<< orphan*/ *) ; 

int videobuf_qbuf(struct videobuf_queue *q, struct v4l2_buffer *b)
{
	struct videobuf_buffer *buf;
	enum v4l2_field field;
	unsigned long flags = 0;
	int retval;

	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	if (b->memory == V4L2_MEMORY_MMAP)
		down_read(&current->mm->mmap_sem);

	videobuf_queue_lock(q);
	retval = -EBUSY;
	if (q->reading) {
		dprintk(1, "qbuf: Reading running...\n");
		goto done;
	}
	retval = -EINVAL;
	if (b->type != q->type) {
		dprintk(1, "qbuf: Wrong type.\n");
		goto done;
	}
	if (b->index >= VIDEO_MAX_FRAME) {
		dprintk(1, "qbuf: index out of range.\n");
		goto done;
	}
	buf = q->bufs[b->index];
	if (NULL == buf) {
		dprintk(1, "qbuf: buffer is null.\n");
		goto done;
	}
	MAGIC_CHECK(buf->magic, MAGIC_BUFFER);
	if (buf->memory != b->memory) {
		dprintk(1, "qbuf: memory type is wrong.\n");
		goto done;
	}
	if (buf->state != VIDEOBUF_NEEDS_INIT && buf->state != VIDEOBUF_IDLE) {
		dprintk(1, "qbuf: buffer is already queued or active.\n");
		goto done;
	}

	if (b->flags & V4L2_BUF_FLAG_INPUT) {
		if (b->input >= q->inputs) {
			dprintk(1, "qbuf: wrong input.\n");
			goto done;
		}
		buf->input = b->input;
	} else {
		buf->input = UNSET;
	}

	switch (b->memory) {
	case V4L2_MEMORY_MMAP:
		if (0 == buf->baddr) {
			dprintk(1, "qbuf: mmap requested "
				   "but buffer addr is zero!\n");
			goto done;
		}
		if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT
		    || q->type == V4L2_BUF_TYPE_VBI_OUTPUT
		    || q->type == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT) {
			buf->size = b->bytesused;
			buf->field = b->field;
			buf->ts = b->timestamp;
		}
		break;
	case V4L2_MEMORY_USERPTR:
		if (b->length < buf->bsize) {
			dprintk(1, "qbuf: buffer length is not enough\n");
			goto done;
		}
		if (VIDEOBUF_NEEDS_INIT != buf->state &&
		    buf->baddr != b->m.userptr)
			q->ops->buf_release(q, buf);
		buf->baddr = b->m.userptr;
		break;
	case V4L2_MEMORY_OVERLAY:
		buf->boff = b->m.offset;
		break;
	default:
		dprintk(1, "qbuf: wrong memory type\n");
		goto done;
	}

	dprintk(1, "qbuf: requesting next field\n");
	field = videobuf_next_field(q);
	retval = q->ops->buf_prepare(q, buf, field);
	if (0 != retval) {
		dprintk(1, "qbuf: buffer_prepare returned %d\n", retval);
		goto done;
	}

	list_add_tail(&buf->stream, &q->stream);
	if (q->streaming) {
		spin_lock_irqsave(q->irqlock, flags);
		q->ops->buf_queue(q, buf);
		spin_unlock_irqrestore(q->irqlock, flags);
	}
	dprintk(1, "qbuf: succeeded\n");
	retval = 0;
	wake_up_interruptible_sync(&q->wait);

done:
	videobuf_queue_unlock(q);

	if (b->memory == V4L2_MEMORY_MMAP)
		up_read(&current->mm->mmap_sem);

	return retval;
}