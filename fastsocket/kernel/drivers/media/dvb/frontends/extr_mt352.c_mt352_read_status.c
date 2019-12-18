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
struct mt352_state {int dummy; } ;
struct dvb_frontend {struct mt352_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int EREMOTEIO ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  STATUS_0 ; 
 int /*<<< orphan*/  STATUS_1 ; 
 int /*<<< orphan*/  STATUS_3 ; 
 int mt352_read_register (struct mt352_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt352_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct mt352_state* state = fe->demodulator_priv;
	int s0, s1, s3;

	/* FIXME:
	 *
	 * The MT352 design manual from Zarlink states (page 46-47):
	 *
	 * Notes about the TUNER_GO register:
	 *
	 * If the Read_Tuner_Byte (bit-1) is activated, then the tuner status
	 * byte is copied from the tuner to the STATUS_3 register and
	 * completion of the read operation is indicated by bit-5 of the
	 * INTERRUPT_3 register.
	 */

	if ((s0 = mt352_read_register(state, STATUS_0)) < 0)
		return -EREMOTEIO;
	if ((s1 = mt352_read_register(state, STATUS_1)) < 0)
		return -EREMOTEIO;
	if ((s3 = mt352_read_register(state, STATUS_3)) < 0)
		return -EREMOTEIO;

	*status = 0;
	if (s0 & (1 << 4))
		*status |= FE_HAS_CARRIER;
	if (s0 & (1 << 1))
		*status |= FE_HAS_VITERBI;
	if (s0 & (1 << 5))
		*status |= FE_HAS_LOCK;
	if (s1 & (1 << 1))
		*status |= FE_HAS_SYNC;
	if (s3 & (1 << 6))
		*status |= FE_HAS_SIGNAL;

	if ((*status & (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC)) !=
		      (FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC))
		*status &= ~FE_HAS_LOCK;

	return 0;
}