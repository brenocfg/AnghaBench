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
typedef  int v4l2_std_id ;
struct video_data {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int V4L2_STD_NTSC ; 
 int /*<<< orphan*/  VIDIOC_G_STD ; 
 int v4l2_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int first_field(const struct video_data *s)
{
    int res;
    v4l2_std_id std;

    res = v4l2_ioctl(s->fd, VIDIOC_G_STD, &std);
    if (res < 0)
        return 0;
    if (std & V4L2_STD_NTSC)
        return 0;

    return 1;
}