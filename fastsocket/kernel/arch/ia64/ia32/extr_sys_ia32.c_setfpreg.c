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
struct TYPE_2__ {int fcr; int fsr; int fir; int fdr; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */

__attribute__((used)) static void setfpreg(struct task_struct *task, int regno, int val)
{
	switch (regno / sizeof(int)) {
	case 0:
		task->thread.fcr = (task->thread.fcr & (~0x1f3f))
			| (val & 0x1f3f);
		break;
	case 1:
		task->thread.fsr = (task->thread.fsr & (~0xffff)) | val;
		break;
	case 2:
		task->thread.fsr = (task->thread.fsr & (~0xffff0000))
			| (val << 16);
		break;
	case 3:
		task->thread.fir = (task->thread.fir & (~0xffffffff)) | val;
		break;
	case 5:
		task->thread.fdr = (task->thread.fdr & (~0xffffffff)) | val;
		break;
	}
}