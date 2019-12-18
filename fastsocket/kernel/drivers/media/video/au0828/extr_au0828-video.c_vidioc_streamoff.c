#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct au0828_fh {scalar_t__ type; int /*<<< orphan*/  vb_vbiq; int /*<<< orphan*/  vb_vidq; int /*<<< orphan*/  resources; struct au0828_dev* dev; } ;
struct au0828_dev {int /*<<< orphan*/  vbi_timeout; scalar_t__ vbi_timeout_running; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vid_timeout; scalar_t__ vid_timeout_running; int /*<<< orphan*/  resources; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* audio_setup ) (struct au0828_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AU0828_MAX_INPUT ; 
 int /*<<< orphan*/  AU0828_RESOURCE_VBI ; 
 int /*<<< orphan*/  AU0828_RESOURCE_VIDEO ; 
 TYPE_1__ AUVI_INPUT (int) ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int au0828_stream_interrupt (struct au0828_dev*) ; 
 int check_dev (struct au0828_dev*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct au0828_fh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free (struct au0828_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  stub1 (struct au0828_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  videobuf_streamoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *priv,
			    enum v4l2_buf_type type)
{
	struct au0828_fh      *fh  = priv;
	struct au0828_dev     *dev = fh->dev;
	int                   rc;
	int                   i;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (fh->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    fh->type != V4L2_BUF_TYPE_VBI_CAPTURE)
		return -EINVAL;
	if (type != fh->type)
		return -EINVAL;

	dprintk(1, "vidioc_streamoff fh=%p t=%d fh->res=%d dev->res=%d\n",
		fh, type, fh->resources, dev->resources);

	if (fh->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		dev->vid_timeout_running = 0;
		del_timer_sync(&dev->vid_timeout);

		v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);
		rc = au0828_stream_interrupt(dev);
		if (rc != 0)
			return rc;

		for (i = 0; i < AU0828_MAX_INPUT; i++) {
			if (AUVI_INPUT(i).audio_setup == NULL)
				continue;
			(AUVI_INPUT(i).audio_setup)(dev, 0);
		}

		videobuf_streamoff(&fh->vb_vidq);
		res_free(fh, AU0828_RESOURCE_VIDEO);
	} else if (fh->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
		dev->vbi_timeout_running = 0;
		del_timer_sync(&dev->vbi_timeout);

		videobuf_streamoff(&fh->vb_vbiq);
		res_free(fh, AU0828_RESOURCE_VBI);
	}

	return 0;
}