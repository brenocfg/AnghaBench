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
struct vp7045_fe_state {int /*<<< orphan*/  d; } ;
struct dvb_frontend {struct vp7045_fe_state* demodulator_priv; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int vp7045_read_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vp7045_fe_read_status(struct dvb_frontend* fe, fe_status_t *status)
{
	struct vp7045_fe_state *state = fe->demodulator_priv;
	u8 s0 = vp7045_read_reg(state->d,0x00),
	   s1 = vp7045_read_reg(state->d,0x01),
	   s3 = vp7045_read_reg(state->d,0x03);

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