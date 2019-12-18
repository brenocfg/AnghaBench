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
struct v4l2_frequency {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  get_v4l2_dev (struct file*) ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 

__attribute__((used)) static int radio_si4713_g_frequency(struct file *file, void *p,
						struct v4l2_frequency *vf)
{
	return v4l2_device_call_until_err(get_v4l2_dev(file), 0, tuner,
							g_frequency, vf);
}