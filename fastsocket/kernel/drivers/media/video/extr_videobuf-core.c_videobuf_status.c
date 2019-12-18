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
struct videobuf_queue {TYPE_1__* int_ops; } ;
struct videobuf_buffer {int memory; int state; scalar_t__ input; int field_count; int /*<<< orphan*/  size; int /*<<< orphan*/  ts; int /*<<< orphan*/  field; scalar_t__ map; int /*<<< orphan*/  boff; int /*<<< orphan*/  bsize; int /*<<< orphan*/  baddr; int /*<<< orphan*/  i; int /*<<< orphan*/  magic; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  userptr; } ;
struct v4l2_buffer {int type; int memory; scalar_t__ input; int sequence; int /*<<< orphan*/  bytesused; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  flags; TYPE_2__ m; int /*<<< orphan*/  length; int /*<<< orphan*/  index; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_3__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_BUFFER ; 
 int /*<<< orphan*/  MAGIC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_QTYPE_OPS ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_DONE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_ERROR ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_INPUT ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_QUEUED ; 
#define  V4L2_MEMORY_MMAP 137 
#define  V4L2_MEMORY_OVERLAY 136 
#define  V4L2_MEMORY_USERPTR 135 
#define  VIDEOBUF_ACTIVE 134 
#define  VIDEOBUF_DONE 133 
#define  VIDEOBUF_ERROR 132 
#define  VIDEOBUF_IDLE 131 
#define  VIDEOBUF_NEEDS_INIT 130 
#define  VIDEOBUF_PREPARED 129 
#define  VIDEOBUF_QUEUED 128 

__attribute__((used)) static void videobuf_status(struct videobuf_queue *q, struct v4l2_buffer *b,
			    struct videobuf_buffer *vb, enum v4l2_buf_type type)
{
	MAGIC_CHECK(vb->magic, MAGIC_BUFFER);
	MAGIC_CHECK(q->int_ops->magic, MAGIC_QTYPE_OPS);

	b->index    = vb->i;
	b->type     = type;

	b->memory   = vb->memory;
	switch (b->memory) {
	case V4L2_MEMORY_MMAP:
		b->m.offset  = vb->boff;
		b->length    = vb->bsize;
		break;
	case V4L2_MEMORY_USERPTR:
		b->m.userptr = vb->baddr;
		b->length    = vb->bsize;
		break;
	case V4L2_MEMORY_OVERLAY:
		b->m.offset  = vb->boff;
		break;
	}

	b->flags    = 0;
	if (vb->map)
		b->flags |= V4L2_BUF_FLAG_MAPPED;

	switch (vb->state) {
	case VIDEOBUF_PREPARED:
	case VIDEOBUF_QUEUED:
	case VIDEOBUF_ACTIVE:
		b->flags |= V4L2_BUF_FLAG_QUEUED;
		break;
	case VIDEOBUF_ERROR:
		b->flags |= V4L2_BUF_FLAG_ERROR;
		/* fall through */
	case VIDEOBUF_DONE:
		b->flags |= V4L2_BUF_FLAG_DONE;
		break;
	case VIDEOBUF_NEEDS_INIT:
	case VIDEOBUF_IDLE:
		/* nothing */
		break;
	}

	if (vb->input != UNSET) {
		b->flags |= V4L2_BUF_FLAG_INPUT;
		b->input  = vb->input;
	}

	b->field     = vb->field;
	b->timestamp = vb->ts;
	b->bytesused = vb->size;
	b->sequence  = vb->field_count >> 1;
}