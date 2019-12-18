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
struct front_face {int type; int /*<<< orphan*/  q; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  logs (struct front_face*) ; 
 scalar_t__ unlikely (int) ; 
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *fh,
				enum v4l2_buf_type type)
{
	struct front_face *front = fh;

	logs(front);
	if (unlikely(type != front->type))
		return -EINVAL;
	return videobuf_streamon(&front->q);
}