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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/  vm_pgoff; } ;
struct file {struct drm_file* private_data; } ;
struct drm_file {TYPE_1__* minor; } ;
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_buf {TYPE_3__* dev_private; } ;
struct TYPE_5__ {struct drm_buf* mmap_buffer; } ;
typedef  TYPE_2__ drm_i810_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  currently_mapped; } ;
typedef  TYPE_3__ drm_i810_buf_priv_t ;
struct TYPE_4__ {struct drm_device* dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  I810_BUF_MAPPED ; 
 int VM_DONTCOPY ; 
 int VM_IO ; 
 scalar_t__ io_remap_pfn_range (struct vm_area_struct*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_mmap_buffers(struct file *filp, struct vm_area_struct *vma)
{
	struct drm_file *priv = filp->private_data;
	struct drm_device *dev;
	drm_i810_private_t *dev_priv;
	struct drm_buf *buf;
	drm_i810_buf_priv_t *buf_priv;

	dev = priv->minor->dev;
	dev_priv = dev->dev_private;
	buf = dev_priv->mmap_buffer;
	buf_priv = buf->dev_private;

	vma->vm_flags |= (VM_IO | VM_DONTCOPY);

	buf_priv->currently_mapped = I810_BUF_MAPPED;

	if (io_remap_pfn_range(vma, vma->vm_start,
			       vma->vm_pgoff,
			       vma->vm_end - vma->vm_start, vma->vm_page_prot))
		return -EAGAIN;
	return 0;
}