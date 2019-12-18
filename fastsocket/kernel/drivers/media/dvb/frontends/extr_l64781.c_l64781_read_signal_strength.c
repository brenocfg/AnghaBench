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
struct l64781_state {int dummy; } ;
struct dvb_frontend {struct l64781_state* demodulator_priv; } ;

/* Variables and functions */
 int l64781_readreg (struct l64781_state*,int) ; 

__attribute__((used)) static int l64781_read_signal_strength(struct dvb_frontend* fe, u16* signal_strength)
{
	struct l64781_state* state = fe->demodulator_priv;

	u8 gain = l64781_readreg (state, 0x0e);
	*signal_strength = (gain << 8) | gain;

	return 0;
}