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
struct poseidon {int /*<<< orphan*/  pm_resume; int /*<<< orphan*/  pm_suspend; } ;
struct front_face {struct poseidon* pd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  logs (struct front_face*) ; 
 int /*<<< orphan*/  pm_video_resume ; 
 int /*<<< orphan*/  pm_video_suspend ; 
 int set_frequency (struct poseidon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *fh,
				struct v4l2_frequency *freq)
{
	struct front_face *front = fh;
	struct poseidon *pd = front->pd;

	logs(front);
#ifdef CONFIG_PM
	pd->pm_suspend = pm_video_suspend;
	pd->pm_resume = pm_video_resume;
#endif
	return set_frequency(pd, freq->frequency);
}