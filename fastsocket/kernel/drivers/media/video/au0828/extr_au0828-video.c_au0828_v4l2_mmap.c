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
struct vm_area_struct {int dummy; } ;
struct file {struct au0828_fh* private_data; } ;
struct au0828_fh {scalar_t__ type; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; struct au0828_dev* dev; } ;
struct au0828_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int check_dev (struct au0828_dev*) ; 
 int videobuf_mmap_mapper (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

__attribute__((used)) static int au0828_v4l2_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct au0828_fh *fh    = filp->private_data;
	struct au0828_dev *dev   = fh->dev;
	int		 rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		rc = videobuf_mmap_mapper(&fh->vb_vidq, vma);
	else if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		rc = videobuf_mmap_mapper(&fh->vb_vbiq, vma);

	return rc;
}