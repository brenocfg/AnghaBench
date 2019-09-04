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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uintptr_t
scrub_frame(uint64_t *bt, int n_frames, int frame)
{
	if (frame < n_frames) {
		return (uintptr_t)(bt[frame]);
	} else {
		return 0;
	}
}