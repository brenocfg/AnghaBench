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
struct mt352_state {int dummy; } ;
struct dvb_frontend {struct mt352_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNR ; 
 int mt352_read_register (struct mt352_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt352_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct mt352_state* state = fe->demodulator_priv;

	u8 _snr = mt352_read_register (state, SNR);
	*snr = (_snr << 8) | _snr;

	return 0;
}