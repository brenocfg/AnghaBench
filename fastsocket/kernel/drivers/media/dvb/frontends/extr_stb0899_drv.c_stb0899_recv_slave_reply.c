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
struct stb0899_state {int dummy; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
struct dvb_diseqc_slave_reply {int msg_len; void** msg; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FIFOBYTENBR ; 
 int /*<<< orphan*/  RXEND ; 
 int /*<<< orphan*/  STB0899_DISFIFO ; 
 int /*<<< orphan*/  STB0899_DISRX_ST0 ; 
 int /*<<< orphan*/  STB0899_DISRX_ST1 ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int) ; 
 void* stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stb0899_wait_diseqc_rxidle (struct stb0899_state*,int) ; 

__attribute__((used)) static int stb0899_recv_slave_reply(struct dvb_frontend *fe, struct dvb_diseqc_slave_reply *reply)
{
	struct stb0899_state *state = fe->demodulator_priv;
	u8 reg, length = 0, i;
	int result;

	if (stb0899_wait_diseqc_rxidle(state, 100) < 0)
		return -ETIMEDOUT;

	reg = stb0899_read_reg(state, STB0899_DISRX_ST0);
	if (STB0899_GETFIELD(RXEND, reg)) {

		reg = stb0899_read_reg(state, STB0899_DISRX_ST1);
		length = STB0899_GETFIELD(FIFOBYTENBR, reg);

		if (length > sizeof (reply->msg)) {
			result = -EOVERFLOW;
			goto exit;
		}
		reply->msg_len = length;

		/* extract data */
		for (i = 0; i < length; i++)
			reply->msg[i] = stb0899_read_reg(state, STB0899_DISFIFO);
	}

	return 0;
exit:

	return result;
}