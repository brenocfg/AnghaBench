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
struct em28xx_fh {int type; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  resources; struct em28xx* dev; } ;
struct em28xx {int /*<<< orphan*/  resources; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int check_dev (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,struct em28xx_fh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ressource (struct em28xx_fh*) ; 
 int /*<<< orphan*/  res_get (struct em28xx_fh*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv,
					enum v4l2_buf_type type)
{
	struct em28xx_fh      *fh  = priv;
	struct em28xx         *dev = fh->dev;
	int                   rc = -EINVAL;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (unlikely(type != fh->type))
		return -EINVAL;

	em28xx_videodbg("vidioc_streamon fh=%p t=%d fh->res=%d dev->res=%d\n",
			fh, type, fh->resources, dev->resources);

	if (unlikely(!res_get(fh, get_ressource(fh))))
		return -EBUSY;

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		rc = videobuf_streamon(&fh->vb_vidq);
	else if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		rc = videobuf_streamon(&fh->vb_vbiq);

	return rc;
}