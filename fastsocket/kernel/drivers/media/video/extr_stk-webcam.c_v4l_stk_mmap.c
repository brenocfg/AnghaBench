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
struct vm_area_struct {unsigned long vm_pgoff; int vm_flags; int /*<<< orphan*/ * vm_ops; struct stk_sio_buffer* vm_private_data; } ;
struct TYPE_3__ {unsigned long offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; TYPE_1__ m; } ;
struct stk_sio_buffer {TYPE_2__ v4lbuf; int /*<<< orphan*/  buffer; } ;
struct stk_camera {unsigned int n_sbufs; struct stk_sio_buffer* sio_bufs; } ;
struct file {struct stk_camera* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 
 int VM_DONTEXPAND ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 int remap_vmalloc_range (struct vm_area_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stk_v4l_vm_open (struct vm_area_struct*) ; 
 int /*<<< orphan*/  stk_v4l_vm_ops ; 

__attribute__((used)) static int v4l_stk_mmap(struct file *fp, struct vm_area_struct *vma)
{
	unsigned int i;
	int ret;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	struct stk_camera *dev = fp->private_data;
	struct stk_sio_buffer *sbuf = NULL;

	if (!(vma->vm_flags & VM_WRITE) || !(vma->vm_flags & VM_SHARED))
		return -EINVAL;

	for (i = 0; i < dev->n_sbufs; i++) {
		if (dev->sio_bufs[i].v4lbuf.m.offset == offset) {
			sbuf = dev->sio_bufs + i;
			break;
		}
	}
	if (sbuf == NULL)
		return -EINVAL;
	ret = remap_vmalloc_range(vma, sbuf->buffer, 0);
	if (ret)
		return ret;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_private_data = sbuf;
	vma->vm_ops = &stk_v4l_vm_ops;
	sbuf->v4lbuf.flags |= V4L2_BUF_FLAG_MAPPED;
	stk_v4l_vm_open(vma);
	return 0;
}