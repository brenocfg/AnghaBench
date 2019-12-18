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
struct slice_mask {int low_slices; int high_slices; } ;

/* Variables and functions */

__attribute__((used)) static int slice_check_fit(struct slice_mask mask, struct slice_mask available)
{
	return (mask.low_slices & available.low_slices) == mask.low_slices &&
		(mask.high_slices & available.high_slices) == mask.high_slices;
}