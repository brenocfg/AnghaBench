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
struct file {struct au0828_fh* private_data; } ;
struct au0828_fh {scalar_t__ type; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; struct au0828_dev* dev; } ;
struct au0828_dev {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  AU0828_RESOURCE_VBI ; 
 int /*<<< orphan*/  AU0828_RESOURCE_VIDEO ; 
 unsigned int POLLERR ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int check_dev (struct au0828_dev*) ; 
 int /*<<< orphan*/  res_get (struct au0828_fh*,int /*<<< orphan*/ ) ; 
 unsigned int videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int au0828_v4l2_poll(struct file *filp, poll_table *wait)
{
	struct au0828_fh *fh = filp->private_data;
	struct au0828_dev *dev = fh->dev;
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		if (!res_get(fh, AU0828_RESOURCE_VIDEO))
			return POLLERR;
		return videobuf_poll_stream(filp, &fh->vb_vidq, wait);
	} else if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
		if (!res_get(fh, AU0828_RESOURCE_VBI))
			return POLLERR;
		return videobuf_poll_stream(filp, &fh->vb_vbiq, wait);
	} else {
		return POLLERR;
	}
}