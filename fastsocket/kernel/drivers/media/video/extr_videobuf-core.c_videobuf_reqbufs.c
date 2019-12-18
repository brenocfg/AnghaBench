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
struct videobuf_queue {scalar_t__ type; TYPE_1__* ops; int /*<<< orphan*/  stream; scalar_t__ streaming; } ;
struct v4l2_requestbuffers {int count; scalar_t__ type; int /*<<< orphan*/  memory; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* buf_setup ) (struct videobuf_queue*,unsigned int*,unsigned int*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int PAGE_ALIGN (unsigned int) ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  V4L2_MEMORY_MMAP ; 
 int /*<<< orphan*/  V4L2_MEMORY_OVERLAY ; 
 int /*<<< orphan*/  V4L2_MEMORY_USERPTR ; 
 unsigned int VIDEO_MAX_FRAME ; 
 int __videobuf_mmap_setup (struct videobuf_queue*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct videobuf_queue*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  videobuf_queue_lock (struct videobuf_queue*) ; 
 int /*<<< orphan*/  videobuf_queue_unlock (struct videobuf_queue*) ; 

int videobuf_reqbufs(struct videobuf_queue *q,
		 struct v4l2_requestbuffers *req)
{
	unsigned int size, count;
	int retval;

	if (req->count < 1) {
		dprintk(1, "reqbufs: count invalid (%d)\n", req->count);
		return -EINVAL;
	}

	if (req->memory != V4L2_MEMORY_MMAP     &&
	    req->memory != V4L2_MEMORY_USERPTR  &&
	    req->memory != V4L2_MEMORY_OVERLAY) {
		dprintk(1, "reqbufs: memory type invalid\n");
		return -EINVAL;
	}

	videobuf_queue_lock(q);
	if (req->type != q->type) {
		dprintk(1, "reqbufs: queue type invalid\n");
		retval = -EINVAL;
		goto done;
	}

	if (q->streaming) {
		dprintk(1, "reqbufs: streaming already exists\n");
		retval = -EBUSY;
		goto done;
	}
	if (!list_empty(&q->stream)) {
		dprintk(1, "reqbufs: stream running\n");
		retval = -EBUSY;
		goto done;
	}

	count = req->count;
	if (count > VIDEO_MAX_FRAME)
		count = VIDEO_MAX_FRAME;
	size = 0;
	q->ops->buf_setup(q, &count, &size);
	dprintk(1, "reqbufs: bufs=%d, size=0x%x [%u pages total]\n",
		count, size,
		(unsigned int)((count * PAGE_ALIGN(size)) >> PAGE_SHIFT));

	retval = __videobuf_mmap_setup(q, count, size, req->memory);
	if (retval < 0) {
		dprintk(1, "reqbufs: mmap setup returned %d\n", retval);
		goto done;
	}

	req->count = retval;
	retval = 0;

 done:
	videobuf_queue_unlock(q);
	return retval;
}