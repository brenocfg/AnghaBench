#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_frequency {int /*<<< orphan*/  frequency; } ;
struct TYPE_2__ {int /*<<< orphan*/  fm_freq; } ;
struct poseidon {TYPE_1__ radio_data; } ;
struct file {struct poseidon* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int fm_get_freq(struct file *file, void *priv,
		       struct v4l2_frequency *argp)
{
	struct poseidon *p = file->private_data;

	argp->frequency = p->radio_data.fm_freq;
	return 0;
}