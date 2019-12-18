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
struct file {int dummy; } ;
struct em28xx_fh {scalar_t__ type; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  resources; struct em28xx* dev; } ;
struct em28xx {int /*<<< orphan*/  resources; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EM28XX_RESOURCE_VBI ; 
 int /*<<< orphan*/  EM28XX_RESOURCE_VIDEO ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int check_dev (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,struct em28xx_fh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ res_check (struct em28xx_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct em28xx_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  videobuf_streamoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *priv,
					enum v4l2_buf_type type)
{
	struct em28xx_fh      *fh  = priv;
	struct em28xx         *dev = fh->dev;
	int                   rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    fh->type != V4L2_BUF_TYPE_VBI_CAPTURE)
		return -EINVAL;
	if (type != fh->type)
		return -EINVAL;

	em28xx_videodbg("vidioc_streamoff fh=%p t=%d fh->res=%d dev->res=%d\n",
			fh, type, fh->resources, dev->resources);

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		if (res_check(fh, EM28XX_RESOURCE_VIDEO)) {
			videobuf_streamoff(&fh->vb_vidq);
			res_free(fh, EM28XX_RESOURCE_VIDEO);
		}
	} else if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
		if (res_check(fh, EM28XX_RESOURCE_VBI)) {
			videobuf_streamoff(&fh->vb_vbiq);
			res_free(fh, EM28XX_RESOURCE_VBI);
		}
	}

	return 0;
}