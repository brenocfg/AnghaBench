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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct TYPE_2__ {scalar_t__ tuner_type; } ;
struct cx88_core {int /*<<< orphan*/  lock; int /*<<< orphan*/  freq; TYPE_1__ board; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  cx88_newstation (struct cx88_core*) ; 
 int /*<<< orphan*/  cx88_set_tvaudio (struct cx88_core*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 

int cx88_set_freq (struct cx88_core  *core,
				struct v4l2_frequency *f)
{
	if (unlikely(UNSET == core->board.tuner_type))
		return -EINVAL;
	if (unlikely(f->tuner != 0))
		return -EINVAL;

	mutex_lock(&core->lock);
	core->freq = f->frequency;
	cx88_newstation(core);
	call_all(core, tuner, s_frequency, f);

	/* When changing channels it is required to reset TVAUDIO */
	msleep (10);
	cx88_set_tvaudio(core);

	mutex_unlock(&core->lock);

	return 0;
}