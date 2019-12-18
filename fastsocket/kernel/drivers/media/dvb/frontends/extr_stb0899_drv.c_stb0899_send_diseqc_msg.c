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
typedef  size_t u8 ;
struct stb0899_state {int dummy; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; size_t* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPRECHARGE ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  STB0899_DISCNTRL1 ; 
 int /*<<< orphan*/  STB0899_DISFIFO ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 size_t stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stb0899_wait_diseqc_fifo_empty (struct stb0899_state*,int) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int stb0899_send_diseqc_msg(struct dvb_frontend *fe, struct dvb_diseqc_master_cmd *cmd)
{
	struct stb0899_state *state = fe->demodulator_priv;
	u8 reg, i;

	if (cmd->msg_len > 8)
		return -EINVAL;

	/* enable FIFO precharge	*/
	reg = stb0899_read_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 1);
	stb0899_write_reg(state, STB0899_DISCNTRL1, reg);
	for (i = 0; i < cmd->msg_len; i++) {
		/* wait for FIFO empty	*/
		if (stb0899_wait_diseqc_fifo_empty(state, 10) < 0)
			return -ETIMEDOUT;

		stb0899_write_reg(state, STB0899_DISFIFO, cmd->msg[i]);
	}
	reg = stb0899_read_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISPRECHARGE, reg, 0);
	stb0899_write_reg(state, STB0899_DISCNTRL1, reg);
	msleep(100);
	return 0;
}