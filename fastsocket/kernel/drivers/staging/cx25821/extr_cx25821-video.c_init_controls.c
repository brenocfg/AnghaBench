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
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct cx25821_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CX25821_CTLS ; 
 TYPE_1__* cx25821_ctls ; 
 int /*<<< orphan*/  cx25821_set_control (struct cx25821_dev*,struct v4l2_control*,int) ; 

__attribute__((used)) static void init_controls(struct cx25821_dev *dev, int chan_num)
{
	struct v4l2_control ctrl;
	int i;
	for (i = 0; i < CX25821_CTLS; i++) {
		ctrl.id = cx25821_ctls[i].id;
		ctrl.value = cx25821_ctls[i].default_value;

		cx25821_set_control(dev, &ctrl, chan_num);
	}
}