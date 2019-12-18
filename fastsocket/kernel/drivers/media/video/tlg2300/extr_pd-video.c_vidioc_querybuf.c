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
struct front_face {int /*<<< orphan*/  q; } ;
struct file {struct front_face* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  logs (struct front_face*) ; 
 int videobuf_querybuf (int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int vidioc_querybuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	struct front_face *front = file->private_data;
	logs(front);
	return videobuf_querybuf(&front->q, b);
}