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
struct i2c_client {int dummy; } ;
struct ch7006_state {int* regs; } ;

/* Variables and functions */
 size_t CH7006_BCLKOUT ; 
 size_t CH7006_BLACK_LEVEL ; 
 size_t CH7006_BWIDTH ; 
 size_t CH7006_CALC_SUBC_INC0 ; 
 size_t CH7006_CLKMODE ; 
 size_t CH7006_CONTRAST ; 
 size_t CH7006_DETECT ; 
 size_t CH7006_DISPMODE ; 
 size_t CH7006_FFILTER ; 
 size_t CH7006_HPOS ; 
 size_t CH7006_INPUT_FORMAT ; 
 size_t CH7006_INPUT_SYNC ; 
 size_t CH7006_PLLM ; 
 size_t CH7006_PLLN ; 
 size_t CH7006_PLLOV ; 
 size_t CH7006_PLL_CONTROL ; 
 size_t CH7006_POV ; 
 size_t CH7006_POWER ; 
 size_t CH7006_START_ACTIVE ; 
 size_t CH7006_SUBC_INC0 ; 
 size_t CH7006_SUBC_INC1 ; 
 size_t CH7006_SUBC_INC2 ; 
 size_t CH7006_SUBC_INC3 ; 
 size_t CH7006_SUBC_INC4 ; 
 size_t CH7006_SUBC_INC5 ; 
 size_t CH7006_SUBC_INC6 ; 
 size_t CH7006_SUBC_INC7 ; 
 size_t CH7006_VPOS ; 
 int /*<<< orphan*/  ch7006_save_reg (struct i2c_client*,struct ch7006_state*,size_t) ; 

void ch7006_state_save(struct i2c_client *client,
		       struct ch7006_state *state)
{
	ch7006_save_reg(client, state, CH7006_POWER);

	ch7006_save_reg(client, state, CH7006_DISPMODE);
	ch7006_save_reg(client, state, CH7006_FFILTER);
	ch7006_save_reg(client, state, CH7006_BWIDTH);
	ch7006_save_reg(client, state, CH7006_INPUT_FORMAT);
	ch7006_save_reg(client, state, CH7006_CLKMODE);
	ch7006_save_reg(client, state, CH7006_START_ACTIVE);
	ch7006_save_reg(client, state, CH7006_POV);
	ch7006_save_reg(client, state, CH7006_BLACK_LEVEL);
	ch7006_save_reg(client, state, CH7006_HPOS);
	ch7006_save_reg(client, state, CH7006_VPOS);
	ch7006_save_reg(client, state, CH7006_INPUT_SYNC);
	ch7006_save_reg(client, state, CH7006_DETECT);
	ch7006_save_reg(client, state, CH7006_CONTRAST);
	ch7006_save_reg(client, state, CH7006_PLLOV);
	ch7006_save_reg(client, state, CH7006_PLLM);
	ch7006_save_reg(client, state, CH7006_PLLN);
	ch7006_save_reg(client, state, CH7006_BCLKOUT);
	ch7006_save_reg(client, state, CH7006_SUBC_INC0);
	ch7006_save_reg(client, state, CH7006_SUBC_INC1);
	ch7006_save_reg(client, state, CH7006_SUBC_INC2);
	ch7006_save_reg(client, state, CH7006_SUBC_INC3);
	ch7006_save_reg(client, state, CH7006_SUBC_INC4);
	ch7006_save_reg(client, state, CH7006_SUBC_INC5);
	ch7006_save_reg(client, state, CH7006_SUBC_INC6);
	ch7006_save_reg(client, state, CH7006_SUBC_INC7);
	ch7006_save_reg(client, state, CH7006_PLL_CONTROL);
	ch7006_save_reg(client, state, CH7006_CALC_SUBC_INC0);

	state->regs[CH7006_FFILTER] = (state->regs[CH7006_FFILTER] & 0xf0) |
		(state->regs[CH7006_FFILTER] & 0x0c) >> 2 |
		(state->regs[CH7006_FFILTER] & 0x03) << 2;
}