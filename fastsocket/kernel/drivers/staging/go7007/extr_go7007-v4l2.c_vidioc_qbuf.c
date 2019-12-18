#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_buffer {scalar_t__ type; scalar_t__ memory; size_t index; } ;
struct go7007_file {size_t buf_count; int /*<<< orphan*/  lock; struct go7007_buffer* bufs; struct go7007* go; } ;
struct go7007_buffer {scalar_t__ state; int offset; int user_addr; int page_count; int /*<<< orphan*/  stream; int /*<<< orphan*/ * pages; scalar_t__ modet_active; scalar_t__ frame_offset; scalar_t__ bytesused; int /*<<< orphan*/  mapped; } ;
struct go7007 {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  stream; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_4__ {TYPE_2__* mm; } ;

/* Variables and functions */
 scalar_t__ BUF_STATE_IDLE ; 
 scalar_t__ BUF_STATE_QUEUED ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 void* GO7007_BUF_PAGES ; 
 int PAGE_MASK ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int get_user_pages (TYPE_1__*,TYPE_2__*,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
	struct go7007_file *gofh = priv;
	struct go7007 *go = gofh->go;
	struct go7007_buffer *gobuf;
	unsigned long flags;
	int retval = -EINVAL;
	int ret;

	if (buf->type != V4L2_BUF_TYPE_VIDEO_CAPTURE ||
			buf->memory != V4L2_MEMORY_MMAP)
		return retval;

	mutex_lock(&gofh->lock);
	if (buf->index < 0 || buf->index >= gofh->buf_count)
		goto unlock_and_return;

	gobuf = &gofh->bufs[buf->index];
	if (!gobuf->mapped)
		goto unlock_and_return;

	retval = -EBUSY;
	if (gobuf->state != BUF_STATE_IDLE)
		goto unlock_and_return;

	/* offset will be 0 until we really support USERPTR streaming */
	gobuf->offset = gobuf->user_addr & ~PAGE_MASK;
	gobuf->bytesused = 0;
	gobuf->frame_offset = 0;
	gobuf->modet_active = 0;
	if (gobuf->offset > 0)
		gobuf->page_count = GO7007_BUF_PAGES + 1;
	else
		gobuf->page_count = GO7007_BUF_PAGES;

	retval = -ENOMEM;
	down_read(&current->mm->mmap_sem);
	ret = get_user_pages(current, current->mm,
			gobuf->user_addr & PAGE_MASK, gobuf->page_count,
			1, 1, gobuf->pages, NULL);
	up_read(&current->mm->mmap_sem);

	if (ret != gobuf->page_count) {
		int i;
		for (i = 0; i < ret; ++i)
			page_cache_release(gobuf->pages[i]);
		gobuf->page_count = 0;
		goto unlock_and_return;
	}

	gobuf->state = BUF_STATE_QUEUED;
	spin_lock_irqsave(&go->spinlock, flags);
	list_add_tail(&gobuf->stream, &go->stream);
	spin_unlock_irqrestore(&go->spinlock, flags);
	mutex_unlock(&gofh->lock);

	return 0;

unlock_and_return:
	mutex_unlock(&gofh->lock);
	return retval;
}