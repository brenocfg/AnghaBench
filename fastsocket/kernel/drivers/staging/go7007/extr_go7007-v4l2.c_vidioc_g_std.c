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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {int standard; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GO7007_STD_NTSC 129 
#define  GO7007_STD_PAL 128 
 int /*<<< orphan*/  V4L2_STD_NTSC ; 
 int /*<<< orphan*/  V4L2_STD_PAL ; 

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *std)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;

	switch (go->standard) {
	case GO7007_STD_NTSC:
		*std = V4L2_STD_NTSC;
		break;
	case GO7007_STD_PAL:
		*std = V4L2_STD_PAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}