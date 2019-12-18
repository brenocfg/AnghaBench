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
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib7000p_sad_calib(struct dib7000p_state *state)
{
/* internal */
//	dib7000p_write_word(state, 72, (3 << 14) | (1 << 12) | (524 << 0)); // sampling clock of the SAD is writting in set_bandwidth
	dib7000p_write_word(state, 73, (0 << 1) | (0 << 0));
	dib7000p_write_word(state, 74, 776); // 0.625*3.3 / 4096

	/* do the calibration */
	dib7000p_write_word(state, 73, (1 << 0));
	dib7000p_write_word(state, 73, (0 << 0));

	msleep(1);

	return 0;
}