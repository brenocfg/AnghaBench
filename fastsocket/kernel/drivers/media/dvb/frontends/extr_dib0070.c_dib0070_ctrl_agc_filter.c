#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct dvb_frontend {struct dib0070_state* tuner_priv; } ;
struct dib0070_state {TYPE_1__* cfg; } ;
struct TYPE_2__ {int vga_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0070_write_reg (struct dib0070_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

void dib0070_ctrl_agc_filter(struct dvb_frontend *fe, u8 open)
{
	struct dib0070_state *state = fe->tuner_priv;

	if (open) {
		dib0070_write_reg(state, 0x1b, 0xff00);
		dib0070_write_reg(state, 0x1a, 0x0000);
	} else {
		dib0070_write_reg(state, 0x1b, 0x4112);
	if (state->cfg->vga_filter != 0) {
		dib0070_write_reg(state, 0x1a, state->cfg->vga_filter);
		dprintk("vga filter register is set to %x", state->cfg->vga_filter);
	} else
		dib0070_write_reg(state, 0x1a, 0x0009);
	}
}