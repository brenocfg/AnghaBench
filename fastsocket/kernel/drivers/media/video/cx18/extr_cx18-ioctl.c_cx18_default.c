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
typedef  int u32 ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_GPIO_RESET_Z8F0811 ; 
 int /*<<< orphan*/  CX18_HW_GPIO_RESET_CTRL ; 
 long EINVAL ; 
#define  VIDIOC_INT_RESET 128 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx18_call_hw (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset ; 

__attribute__((used)) static long cx18_default(struct file *file, void *fh, int cmd, void *arg)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;

	switch (cmd) {
	case VIDIOC_INT_RESET: {
		u32 val = *(u32 *)arg;

		if ((val == 0) || (val & 0x01))
			cx18_call_hw(cx, CX18_HW_GPIO_RESET_CTRL, core, reset,
				     (u32) CX18_GPIO_RESET_Z8F0811);
		break;
	}

	default:
		return -EINVAL;
	}
	return 0;
}