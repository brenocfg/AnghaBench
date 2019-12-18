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
struct poseidon {int /*<<< orphan*/  pm_resume; int /*<<< orphan*/  pm_suspend; struct file* file_for_stream; } ;
struct file {struct poseidon* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_fm_resume ; 
 int /*<<< orphan*/  pm_fm_suspend ; 
 int set_frequency (struct poseidon*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm_set_freq(struct file *file, void *priv,
		       struct v4l2_frequency *argp)
{
	struct poseidon *p = file->private_data;

	p->file_for_stream  = file;
#ifdef CONFIG_PM
	p->pm_suspend = pm_fm_suspend;
	p->pm_resume  = pm_fm_resume;
#endif
	return set_frequency(p, argp->frequency);
}