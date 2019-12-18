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
typedef  int fe_status_t ;

/* Variables and functions */
 int EREMOTEIO ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  MB86A16_FRAMESYNC ; 
 int /*<<< orphan*/  MB86A16_SIG1 ; 
 int /*<<< orphan*/  MB86A16_SIG2 ; 
 int /*<<< orphan*/  MB86A16_STATUS ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int mb86a16_read (struct mb86a16_state*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mb86a16_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	u8 stat, stat2;
	struct mb86a16_state *state = fe->demodulator_priv;

	*status = 0;

	if (mb86a16_read(state, MB86A16_SIG1, &stat) != 2)
		goto err;
	if (mb86a16_read(state, MB86A16_SIG2, &stat2) != 2)
		goto err;
	if ((stat > 25) && (stat2 > 25))
		*status |= FE_HAS_SIGNAL;
	if ((stat > 45) && (stat2 > 45))
		*status |= FE_HAS_CARRIER;

	if (mb86a16_read(state, MB86A16_STATUS, &stat) != 2)
		goto err;

	if (stat & 0x01)
		*status |= FE_HAS_SYNC;
	if (stat & 0x01)
		*status |= FE_HAS_VITERBI;

	if (mb86a16_read(state, MB86A16_FRAMESYNC, &stat) != 2)
		goto err;

	if ((stat & 0x0f) && (*status & FE_HAS_VITERBI))
		*status |= FE_HAS_LOCK;

	return 0;

err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;
}