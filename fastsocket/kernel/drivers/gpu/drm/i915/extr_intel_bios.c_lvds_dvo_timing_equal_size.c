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
struct lvds_dvo_timing {scalar_t__ hactive_hi; scalar_t__ hactive_lo; scalar_t__ hsync_off_hi; scalar_t__ hsync_off_lo; scalar_t__ hsync_pulse_width; scalar_t__ hblank_hi; scalar_t__ hblank_lo; scalar_t__ vactive_hi; scalar_t__ vactive_lo; scalar_t__ vsync_off; scalar_t__ vsync_pulse_width; scalar_t__ vblank_hi; scalar_t__ vblank_lo; } ;

/* Variables and functions */

__attribute__((used)) static bool
lvds_dvo_timing_equal_size(const struct lvds_dvo_timing *a,
			   const struct lvds_dvo_timing *b)
{
	if (a->hactive_hi != b->hactive_hi ||
	    a->hactive_lo != b->hactive_lo)
		return false;

	if (a->hsync_off_hi != b->hsync_off_hi ||
	    a->hsync_off_lo != b->hsync_off_lo)
		return false;

	if (a->hsync_pulse_width != b->hsync_pulse_width)
		return false;

	if (a->hblank_hi != b->hblank_hi ||
	    a->hblank_lo != b->hblank_lo)
		return false;

	if (a->vactive_hi != b->vactive_hi ||
	    a->vactive_lo != b->vactive_lo)
		return false;

	if (a->vsync_off != b->vsync_off)
		return false;

	if (a->vsync_pulse_width != b->vsync_pulse_width)
		return false;

	if (a->vblank_hi != b->vblank_hi ||
	    a->vblank_lo != b->vblank_lo)
		return false;

	return true;
}