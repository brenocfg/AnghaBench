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
typedef  int u16 ;
struct dib0090_state {int wbd_offset; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib0090_wbd_slopes ; 
 scalar_t__ slopes_to_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s16 dib0090_wbd_to_db(struct dib0090_state *state, u16 wbd)
{
	wbd &= 0x3ff;
	if (wbd < state->wbd_offset)
		wbd = 0;
	else
		wbd -= state->wbd_offset;
	/* -64dB is the floor */
	return -640 + (s16) slopes_to_scale(dib0090_wbd_slopes, ARRAY_SIZE(dib0090_wbd_slopes), wbd);
}