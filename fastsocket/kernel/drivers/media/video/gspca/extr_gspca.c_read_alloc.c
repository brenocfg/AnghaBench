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
struct v4l2_requestbuffers {int count; int index; void* memory; void* type; } ;
struct v4l2_buffer {int count; int index; void* memory; void* type; } ;
struct gspca_dev {scalar_t__ nframes; int nbufread; void* memory; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 void* GSPCA_MEMORY_READ ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  memset (struct v4l2_requestbuffers*,int /*<<< orphan*/ ,int) ; 
 int vidioc_qbuf (struct file*,struct gspca_dev*,struct v4l2_requestbuffers*) ; 
 int vidioc_reqbufs (struct file*,struct gspca_dev*,struct v4l2_requestbuffers*) ; 
 int vidioc_streamon (struct file*,struct gspca_dev*,void*) ; 

__attribute__((used)) static int read_alloc(struct gspca_dev *gspca_dev,
			struct file *file)
{
	struct v4l2_buffer v4l2_buf;
	int i, ret;

	PDEBUG(D_STREAM, "read alloc");
	if (gspca_dev->nframes == 0) {
		struct v4l2_requestbuffers rb;

		memset(&rb, 0, sizeof rb);
		rb.count = gspca_dev->nbufread;
		rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		rb.memory = GSPCA_MEMORY_READ;
		ret = vidioc_reqbufs(file, gspca_dev, &rb);
		if (ret != 0) {
			PDEBUG(D_STREAM, "read reqbuf err %d", ret);
			return ret;
		}
		memset(&v4l2_buf, 0, sizeof v4l2_buf);
		v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		v4l2_buf.memory = GSPCA_MEMORY_READ;
		for (i = 0; i < gspca_dev->nbufread; i++) {
			v4l2_buf.index = i;
			ret = vidioc_qbuf(file, gspca_dev, &v4l2_buf);
			if (ret != 0) {
				PDEBUG(D_STREAM, "read qbuf err: %d", ret);
				return ret;
			}
		}
		gspca_dev->memory = GSPCA_MEMORY_READ;
	}

	/* start streaming */
	ret = vidioc_streamon(file, gspca_dev, V4L2_BUF_TYPE_VIDEO_CAPTURE);
	if (ret != 0)
		PDEBUG(D_STREAM, "read streamon err %d", ret);
	return ret;
}