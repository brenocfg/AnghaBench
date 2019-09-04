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
 uintptr_t VM_KERNEL_UNSLIDE (uintptr_t) ; 

__attribute__((used)) static inline uintptr_t
scrub_word(uintptr_t *bt, int n_frames, int frame, bool kern)
{
	if (frame < n_frames) {
		if (kern) {
			return VM_KERNEL_UNSLIDE(bt[frame]);
		} else {
			return bt[frame];
		}
	} else {
		return 0;
	}
}