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
struct zoltrix {int dummy; } ;
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct zoltrix* video_drvdata (struct file*) ; 
 scalar_t__ zol_setfreq (struct zoltrix*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct zoltrix *zol = video_drvdata(file);

	if (zol_setfreq(zol, f->frequency) != 0)
		return -EINVAL;
	return 0;
}