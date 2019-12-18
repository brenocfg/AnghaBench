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
typedef  int u32 ;
struct lgdt3305_state {int dummy; } ;
struct dvb_frontend {struct lgdt3305_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LGDT3305_FEC_PKT_ERR_1 ; 
 int /*<<< orphan*/  LGDT3305_FEC_PKT_ERR_2 ; 
 int read_reg (struct lgdt3305_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lgdt3305_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct lgdt3305_state *state = fe->demodulator_priv;

	*ucblocks =
		(read_reg(state, LGDT3305_FEC_PKT_ERR_1) << 8) |
		(read_reg(state, LGDT3305_FEC_PKT_ERR_2) & 0xff);

	return 0;
}