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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct dib0090_state {scalar_t__ const* rf_ramp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0090_read_reg (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dib0090_write_regs (struct dib0090_state*,int,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib0090_set_rframp_pwm(struct dib0090_state *state, const u16 * cfg)
{
	state->rf_ramp = cfg;

	dib0090_write_reg(state, 0x2a, 0xffff);

	dprintk("total RF gain: %ddB, step: %d", (u32) cfg[0], dib0090_read_reg(state, 0x2a));

	dib0090_write_regs(state, 0x2c, cfg + 3, 6);
	dib0090_write_regs(state, 0x3e, cfg + 9, 2);
}