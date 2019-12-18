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
typedef  int u8 ;
struct ves1820_state {int reg0; TYPE_1__* config; } ;
typedef  scalar_t__ fe_spectral_inversion_t ;
struct TYPE_2__ {int /*<<< orphan*/  invert; } ;

/* Variables and functions */
 scalar_t__ INVERSION_OFF ; 
 scalar_t__ INVERSION_ON ; 
 int /*<<< orphan*/  ves1820_writereg (struct ves1820_state*,int,int) ; 

__attribute__((used)) static int ves1820_setup_reg0(struct ves1820_state *state, u8 reg0, fe_spectral_inversion_t inversion)
{
	reg0 |= state->reg0 & 0x62;

	if (INVERSION_ON == inversion) {
		if (!state->config->invert) reg0 |= 0x20;
		else reg0 &= ~0x20;
	} else if (INVERSION_OFF == inversion) {
		if (!state->config->invert) reg0 &= ~0x20;
		else reg0 |= 0x20;
	}

	ves1820_writereg(state, 0x00, reg0 & 0xfe);
	ves1820_writereg(state, 0x00, reg0 | 0x01);

	state->reg0 = reg0;

	return 0;
}