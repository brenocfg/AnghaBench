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
struct v4l2_frequency {scalar_t__ tuner; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  ivtv_call_all (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  tuner ; 

__attribute__((used)) static int ivtv_g_frequency(struct file *file, void *fh, struct v4l2_frequency *vf)
{
	struct ivtv *itv = ((struct ivtv_open_id *)fh)->itv;

	if (vf->tuner != 0)
		return -EINVAL;

	ivtv_call_all(itv, tuner, g_frequency, vf);
	return 0;
}