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
 int /*<<< orphan*/  fcs ; 
 int /*<<< orphan*/  fip ; 
 int /*<<< orphan*/  foo ; 
 int /*<<< orphan*/  fop ; 
 int /*<<< orphan*/  fos ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mxcsr ; 
 int /*<<< orphan*/  swd ; 
 int /*<<< orphan*/  twd ; 

__attribute__((used)) static void getfpxreg(struct task_struct *task, int start, int end, char *buf)
{
	int min_val;

	min_val = min(end, OFFSET(fop));
	while (start < min_val) {
		if (start == OFFSET(cwd))
			*((short *)buf) = task->thread.fcr & 0xffff;
		else if (start == OFFSET(swd))
			*((short *)buf) = task->thread.fsr & 0xffff;
		else if (start == OFFSET(twd))
			*((short *)buf) = (task->thread.fsr>>16) & 0xffff;
		buf += 2;
		start += 2;
	}
	/* skip fop element */
	if (start == OFFSET(fop)) {
		start += 2;
		buf += 2;
	}
	while (start < end) {
		if (start == OFFSET(fip))
			*((int *)buf) = task->thread.fir;
		else if (start == OFFSET(fcs))
			*((int *)buf) = (task->thread.fir>>32) & 0xffff;
		else if (start == OFFSET(foo))
			*((int *)buf) = task->thread.fdr;
		else if (start == OFFSET(fos))
			*((int *)buf) = (task->thread.fdr>>32) & 0xffff;
		else if (start == OFFSET(mxcsr))
			*((int *)buf) = ((task->thread.fcr>>32) & 0xff80)
					 | ((task->thread.fsr>>32) & 0x3f);
		buf += 4;
		start += 4;
	}
}