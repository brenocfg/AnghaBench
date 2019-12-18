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
struct drm_mm {unsigned long scan_color; unsigned int scan_alignment; unsigned long scan_size; int /*<<< orphan*/ * prev_scanned_node; scalar_t__ scan_check_range; scalar_t__ scan_hit_end; scalar_t__ scan_hit_start; scalar_t__ scanned_blocks; } ;

/* Variables and functions */

void drm_mm_init_scan(struct drm_mm *mm,
		      unsigned long size,
		      unsigned alignment,
		      unsigned long color)
{
	mm->scan_color = color;
	mm->scan_alignment = alignment;
	mm->scan_size = size;
	mm->scanned_blocks = 0;
	mm->scan_hit_start = 0;
	mm->scan_hit_end = 0;
	mm->scan_check_range = 0;
	mm->prev_scanned_node = NULL;
}