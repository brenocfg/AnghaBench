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
 int OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cwd ; 
 int /*<<< orphan*/  fip ; 
 int /*<<< orphan*/  foo ; 
 int /*<<< orphan*/  fop ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mxcsr ; 
 int /*<<< orphan*/  swd ; 
 int /*<<< orphan*/  twd ; 

__attribute__((used)) static void setfpxreg(struct task_struct *task, int start, int end, char *buf)
{
	int min_val, num32;
	short num;
	unsigned long num64;

	min_val = min(end, OFFSET(fop));
	while (start < min_val) {
		num = *((short *)buf);
		if (start == OFFSET(cwd)) {
			task->thread.fcr = (task->thread.fcr & (~0x1f3f))
						| (num & 0x1f3f);
		} else if (start == OFFSET(swd)) {
			task->thread.fsr = (task->thread.fsr & (~0xffff)) | num;
		} else if (start == OFFSET(twd)) {
			task->thread.fsr = (task->thread.fsr & (~0xffff0000))
				| (((int)num) << 16);
		}
		buf += 2;
		start += 2;
	}
	/* skip fop element */
	if (start == OFFSET(fop)) {
		start += 2;
		buf += 2;
	}
	while (start < end) {
		num32 = *((int *)buf);
		if (start == OFFSET(fip))
			task->thread.fir = (task->thread.fir & (~0xffffffff))
						 | num32;
		else if (start == OFFSET(foo))
			task->thread.fdr = (task->thread.fdr & (~0xffffffff))
						 | num32;
		else if (start == OFFSET(mxcsr)) {
			num64 = num32 & 0xff10;
			task->thread.fcr = (task->thread.fcr &
				(~0xff1000000000UL)) | (num64<<32);
			num64 = num32 & 0x3f;
			task->thread.fsr = (task->thread.fsr &
				(~0x3f00000000UL)) | (num64<<32);
		}
		buf += 4;
		start += 4;
	}
}