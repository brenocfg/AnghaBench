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
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct aztech {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  az_setfreq (struct aztech*,int /*<<< orphan*/ ) ; 
 struct aztech* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct aztech *az = video_drvdata(file);

	az_setfreq(az, f->frequency);
	return 0;
}