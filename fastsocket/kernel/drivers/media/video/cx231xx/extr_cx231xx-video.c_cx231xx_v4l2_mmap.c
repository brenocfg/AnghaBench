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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {int /*<<< orphan*/  vb_vidq; struct cx231xx* dev; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int check_dev (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_videodbg (char*,unsigned long,unsigned long,int) ; 
 int res_get (struct cx231xx_fh*) ; 
 scalar_t__ unlikely (int) ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

__attribute__((used)) static int cx231xx_v4l2_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct cx231xx_fh *fh = filp->private_data;
	struct cx231xx *dev = fh->dev;
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	rc = res_get(fh);

	if (unlikely(rc < 0))
		return rc;

	rc = videobuf_mmap_mapper(&fh->vb_vidq, vma);

	cx231xx_videodbg("vma start=0x%08lx, size=%ld, ret=%d\n",
			 (unsigned long)vma->vm_start,
			 (unsigned long)vma->vm_end -
			 (unsigned long)vma->vm_start, rc);

	return rc;
}