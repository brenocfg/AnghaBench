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

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 size_t rBufB ; 
 scalar_t__ rbv_present ; 
 size_t vBufB ; 
 size_t vDirB ; 
 int* via2 ; 

__attribute__((used)) static void via_shutdown(void)
{
	if (rbv_present) {
		via2[rBufB] &= ~0x04;
	} else {
		/* Direction of vDirB is output */
		via2[vDirB] |= 0x04;
		/* Send a value of 0 on that line */
		via2[vBufB] &= ~0x04;
		mdelay(1000);
	}
}