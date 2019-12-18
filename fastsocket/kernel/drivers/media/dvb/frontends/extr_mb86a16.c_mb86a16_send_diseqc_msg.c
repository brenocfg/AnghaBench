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
struct mb86a16_state {int dummy; } ;
struct dvb_frontend {struct mb86a16_state* demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; int* msg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EREMOTEIO ; 
 int MB86A16_DCC1 ; 
 int MB86A16_DCC1_DISTA ; 
 int MB86A16_DCCOUT ; 
 int MB86A16_DCCOUT_DISEN ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int MB86A16_TONEOUT2 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mb86a16_write (struct mb86a16_state*,int,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_send_diseqc_msg(struct dvb_frontend *fe,
				   struct dvb_diseqc_master_cmd *cmd)
{
	struct mb86a16_state *state = fe->demodulator_priv;
	int i;
	u8 regs;

	if (mb86a16_write(state, MB86A16_DCC1, MB86A16_DCC1_DISTA) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_DCCOUT, 0x00) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_TONEOUT2, 0x04) < 0)
		goto err;

	regs = 0x18;

	if (cmd->msg_len > 5 || cmd->msg_len < 4)
		return -EINVAL;

	for (i = 0; i < cmd->msg_len; i++) {
		if (mb86a16_write(state, regs, cmd->msg[i]) < 0)
			goto err;

		regs++;
	}
	i += 0x90;

	msleep_interruptible(10);

	if (mb86a16_write(state, MB86A16_DCC1, i) < 0)
		goto err;
	if (mb86a16_write(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
		goto err;

	return 0;

err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}