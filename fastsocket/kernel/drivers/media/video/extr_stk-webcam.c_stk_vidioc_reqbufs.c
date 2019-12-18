#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_requestbuffers {scalar_t__ memory; int count; } ;
struct stk_camera {int n_sbufs; struct file* owner; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 scalar_t__ is_streaming (struct stk_camera*) ; 
 int /*<<< orphan*/  stk_allocate_buffers (struct stk_camera*,int) ; 

__attribute__((used)) static int stk_vidioc_reqbufs(struct file *filp,
		void *priv, struct v4l2_requestbuffers *rb)
{
	struct stk_camera *dev = priv;

	if (dev == NULL)
		return -ENODEV;
	if (rb->memory != V4L2_MEMORY_MMAP)
		return -EINVAL;
	if (is_streaming(dev)
		|| (dev->owner && dev->owner != filp))
		return -EBUSY;
	dev->owner = filp;

	/*FIXME If they ask for zero, we must stop streaming and free */
	if (rb->count < 3)
		rb->count = 3;
	/* Arbitrary limit */
	else if (rb->count > 5)
		rb->count = 5;

	stk_allocate_buffers(dev, rb->count);
	rb->count = dev->n_sbufs;
	return 0;
}