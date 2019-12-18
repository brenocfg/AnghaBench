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
struct mb86a16_state {int dummy; } ;
struct dvb_frontend {struct mb86a16_state* demodulator_priv; } ;
typedef  int fe_sec_mini_cmd_t ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_DCC1 ; 
 int MB86A16_DCC1_DISTA ; 
 int MB86A16_DCC1_TBEN ; 
 int MB86A16_DCC1_TBO ; 
 int /*<<< orphan*/  MB86A16_DCCOUT ; 
 int MB86A16_DCCOUT_DISEN ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
#define  SEC_MINI_A 129 
#define  SEC_MINI_B 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mb86a16_write (struct mb86a16_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_send_diseqc_burst(struct dvb_frontend *fe, fe_sec_mini_cmd_t burst)
{
	struct mb86a16_state *state = fe->demodulator_priv;

	switch (burst) {
	case SEC_MINI_A:
		if (mb86a16_write(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_TBEN  |
						       MB86A16_DCC1_TBO) < 0)
			goto err;
		if (mb86a16_write(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			goto err;
		break;
	case SEC_MINI_B:
		if (mb86a16_write(state, MB86A16_DCC1, MB86A16_DCC1_DISTA |
						       MB86A16_DCC1_TBEN) < 0)
			goto err;
		if (mb86a16_write(state, MB86A16_DCCOUT, MB86A16_DCCOUT_DISEN) < 0)
			goto err;
		break;
	}

	return 0;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}