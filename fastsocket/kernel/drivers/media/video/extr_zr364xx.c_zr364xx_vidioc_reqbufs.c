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
struct zr364xx_camera {int /*<<< orphan*/  vb_vidq; } ;
struct v4l2_requestbuffers {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct zr364xx_camera* video_drvdata (struct file*) ; 
 int videobuf_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int zr364xx_vidioc_reqbufs(struct file *file, void *priv,
			  struct v4l2_requestbuffers *p)
{
	int rc;
	struct zr364xx_camera *cam = video_drvdata(file);
	rc = videobuf_reqbufs(&cam->vb_vidq, p);
	return rc;
}