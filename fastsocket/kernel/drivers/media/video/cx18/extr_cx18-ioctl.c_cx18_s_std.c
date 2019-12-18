#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct file {int dummy; } ;
struct cx18_open_id {int /*<<< orphan*/  prio; struct cx18* cx; } ;
struct TYPE_4__ {int count; int* start; } ;
struct TYPE_3__ {int is_50hz; int width; int height; } ;
struct cx18 {int std; int is_60hz; int is_50hz; TYPE_2__ vbi; TYPE_1__ params; int /*<<< orphan*/  ana_capturing; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*,unsigned long long) ; 
 int /*<<< orphan*/  CX18_F_I_RADIO_USER ; 
 int EBUSY ; 
 int EINVAL ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_ALL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_std ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_prio_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int cx18_s_std(struct file *file, void *fh, v4l2_std_id *std)
{
	struct cx18_open_id *id = fh;
	struct cx18 *cx = id->cx;
	int ret;

	ret = v4l2_prio_check(&cx->prio, id->prio);
	if (ret)
		return ret;

	if ((*std & V4L2_STD_ALL) == 0)
		return -EINVAL;

	if (*std == cx->std)
		return 0;

	if (test_bit(CX18_F_I_RADIO_USER, &cx->i_flags) ||
	    atomic_read(&cx->ana_capturing) > 0) {
		/* Switching standard would turn off the radio or mess
		   with already running streams, prevent that by
		   returning EBUSY. */
		return -EBUSY;
	}

	cx->std = *std;
	cx->is_60hz = (*std & V4L2_STD_525_60) ? 1 : 0;
	cx->params.is_50hz = cx->is_50hz = !cx->is_60hz;
	cx->params.width = 720;
	cx->params.height = cx->is_50hz ? 576 : 480;
	cx->vbi.count = cx->is_50hz ? 18 : 12;
	cx->vbi.start[0] = cx->is_50hz ? 6 : 10;
	cx->vbi.start[1] = cx->is_50hz ? 318 : 273;
	CX18_DEBUG_INFO("Switching standard to %llx.\n",
			(unsigned long long) cx->std);

	/* Tuner */
	cx18_call_all(cx, core, s_std, cx->std);
	return 0;
}