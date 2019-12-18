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
struct v4l2_buffer {int dummy; } ;
struct s2255_fh {int /*<<< orphan*/  vb_vidq; } ;
struct file {int f_flags; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int videobuf_dqbuf (int /*<<< orphan*/ *,struct v4l2_buffer*,int) ; 

__attribute__((used)) static int vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *p)
{
	int rc;
	struct s2255_fh *fh = priv;
	rc = videobuf_dqbuf(&fh->vb_vidq, p, file->f_flags & O_NONBLOCK);
	return rc;
}