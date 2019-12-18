#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dib0090_state {int bb_1_def; TYPE_2__* fe; } ;
struct TYPE_3__ {int bandwidth_hz; } ;
struct TYPE_4__ {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 

__attribute__((used)) static void dib0090_set_bandwidth(struct dib0090_state *state)
{
	u16 tmp;

	if (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 5000)
		tmp = (3 << 14);
	else if (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 6000)
		tmp = (2 << 14);
	else if (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 7000)
		tmp = (1 << 14);
	else
		tmp = (0 << 14);

	state->bb_1_def &= 0x3fff;
	state->bb_1_def |= tmp;

	dib0090_write_reg(state, 0x01, state->bb_1_def);	/* be sure that we have the right bb-filter */
}