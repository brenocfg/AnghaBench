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
struct pt_regs {unsigned long windowstart; unsigned long windowbase; int wmask; int* areg; } ;

/* Variables and functions */
 int XCHAL_NUM_AREGS ; 
 scalar_t__ __get_user (unsigned long,int*) ; 
 scalar_t__ copy_to_user (void*,int*,int) ; 

int
flush_window_regs_user(struct pt_regs *regs)
{
	const unsigned long ws = regs->windowstart;
	const unsigned long wb = regs->windowbase;
	unsigned long sp = 0;
	unsigned long wm;
	int err = 1;
	int base;

	/* Return if no other frames. */

	if (regs->wmask == 1)
		return 0;

	/* Rotate windowmask and skip empty frames. */

	wm = (ws >> wb) | (ws << (XCHAL_NUM_AREGS / 4 - wb));
	base = (XCHAL_NUM_AREGS / 4) - (regs->wmask >> 4);
		
	/* For call8 or call12 frames, we need the previous stack pointer. */

	if ((regs->wmask & 2) == 0)
		if (__get_user(sp, (int*)(regs->areg[base * 4 + 1] - 12)))
			goto errout;

	/* Spill frames to stack. */

	while (base < XCHAL_NUM_AREGS / 4) {

		int m = (wm >> base);
		int inc = 0;

		/* Save registers a4..a7 (call8) or a4...a11 (call12) */

		if (m & 2) {			/* call4 */
			inc = 1;

		} else if (m & 4) {		/* call8 */
			if (copy_to_user((void*)(sp - 32),
					   &regs->areg[(base + 1) * 4], 16))
				goto errout;
			inc = 2;

		} else if (m & 8) {	/* call12 */
			if (copy_to_user((void*)(sp - 48),
					   &regs->areg[(base + 1) * 4], 32))
				goto errout;
			inc = 3;
		}

		/* Save current frame a0..a3 under next SP */

		sp = regs->areg[((base + inc) * 4 + 1) % XCHAL_NUM_AREGS];
		if (copy_to_user((void*)(sp - 16), &regs->areg[base * 4], 16))
			goto errout;

		/* Get current stack pointer for next loop iteration. */

		sp = regs->areg[base * 4 + 1];
		base += inc;
	}

	regs->wmask = 1;
	regs->windowstart = 1 << wb;

	return 0;

errout:
	return err;
}