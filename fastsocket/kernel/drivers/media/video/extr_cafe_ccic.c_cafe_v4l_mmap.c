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
struct vm_area_struct {unsigned long vm_pgoff; int vm_flags; int /*<<< orphan*/ * vm_ops; struct cafe_sio_buffer* vm_private_data; } ;
struct file {struct cafe_camera* private_data; } ;
struct TYPE_3__ {unsigned long offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; TYPE_1__ m; } ;
struct cafe_sio_buffer {TYPE_2__ v4lbuf; int /*<<< orphan*/  buffer; } ;
struct cafe_camera {int n_sbufs; int /*<<< orphan*/  s_mutex; struct cafe_sio_buffer* sb_bufs; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int VM_DONTEXPAND ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  cafe_v4l_vm_open (struct vm_area_struct*) ; 
 int /*<<< orphan*/  cafe_v4l_vm_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int remap_vmalloc_range (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cafe_v4l_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct cafe_camera *cam = filp->private_data;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	int ret = -EINVAL;
	int i;
	struct cafe_sio_buffer *sbuf = NULL;

	if (! (vma->vm_flags & VM_WRITE) || ! (vma->vm_flags & VM_SHARED))
		return -EINVAL;
	/*
	 * Find the buffer they are looking for.
	 */
	mutex_lock(&cam->s_mutex);
	for (i = 0; i < cam->n_sbufs; i++)
		if (cam->sb_bufs[i].v4lbuf.m.offset == offset) {
			sbuf = cam->sb_bufs + i;
			break;
		}
	if (sbuf == NULL)
		goto out;

	ret = remap_vmalloc_range(vma, sbuf->buffer, 0);
	if (ret)
		goto out;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_private_data = sbuf;
	vma->vm_ops = &cafe_v4l_vm_ops;
	sbuf->v4lbuf.flags |= V4L2_BUF_FLAG_MAPPED;
	cafe_v4l_vm_open(vma);
	ret = 0;
  out:
	mutex_unlock(&cam->s_mutex);
	return ret;
}