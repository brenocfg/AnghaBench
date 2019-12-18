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
typedef  int u8 ;
typedef  int u16 ;
struct ves1820_state {int dummy; } ;
struct dvb_frontend {struct ves1820_state* demodulator_priv; } ;

/* Variables and functions */
 int ves1820_readreg (struct ves1820_state*,int) ; 

__attribute__((used)) static int ves1820_read_signal_strength(struct dvb_frontend* fe, u16* strength)
{
	struct ves1820_state* state = fe->demodulator_priv;

	u8 gain = ves1820_readreg(state, 0x17);
	*strength = (gain << 8) | gain;

	return 0;
}