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
struct tda8083_state {int dummy; } ;
struct dvb_frontend {struct tda8083_state* demodulator_priv; } ;

/* Variables and functions */
 int tda8083_readreg (struct tda8083_state*,int) ; 

__attribute__((used)) static int tda8083_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct tda8083_state* state = fe->demodulator_priv;

	u8 _snr = tda8083_readreg (state, 0x08);
	*snr = (_snr << 8) | _snr;

	return 0;
}