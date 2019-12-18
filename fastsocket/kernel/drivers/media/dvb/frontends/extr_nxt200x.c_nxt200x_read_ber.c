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
typedef  int u32 ;
struct nxt200x_state {int dummy; } ;
struct dvb_frontend {struct nxt200x_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nxt200x_readreg_multibyte (struct nxt200x_state*,int,int*,int) ; 

__attribute__((used)) static int nxt200x_read_ber(struct dvb_frontend* fe, u32* ber)
{
	struct nxt200x_state* state = fe->demodulator_priv;
	u8 b[3];

	nxt200x_readreg_multibyte(state, 0xE6, b, 3);

	*ber = ((b[0] << 8) + b[1]) * 8;

	return 0;
}