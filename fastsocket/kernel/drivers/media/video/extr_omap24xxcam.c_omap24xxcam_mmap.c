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
struct vm_area_struct {int /*<<< orphan*/  vm_private_data; int /*<<< orphan*/  vm_page_prot; } ;
struct omap24xxcam_fh {int /*<<< orphan*/  vbq; } ;
struct file {struct omap24xxcam_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int omap24xxcam_mmap_buffers (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

__attribute__((used)) static int omap24xxcam_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct omap24xxcam_fh *fh = file->private_data;
	int rval;

	/* let the video-buf mapper check arguments and set-up structures */
	rval = videobuf_mmap_mapper(&fh->vbq, vma);
	if (rval)
		return rval;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/* do mapping to our allocated buffers */
	rval = omap24xxcam_mmap_buffers(file, vma);
	/*
	 * In case of error, free vma->vm_private_data allocated by
	 * videobuf_mmap_mapper.
	 */
	if (rval)
		kfree(vma->vm_private_data);

	return rval;
}