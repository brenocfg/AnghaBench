#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mb86a20s_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct mb86a20s_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  fe_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_HAS_CARRIER ; 
 int /*<<< orphan*/  FE_HAS_LOCK ; 
 int /*<<< orphan*/  FE_HAS_SIGNAL ; 
 int /*<<< orphan*/  FE_HAS_SYNC ; 
 int /*<<< orphan*/  FE_HAS_VITERBI ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int mb86a20s_readreg (struct mb86a20s_state*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mb86a20s_read_status(struct dvb_frontend *fe, fe_status_t *status)
{
	struct mb86a20s_state *state = fe->demodulator_priv;
	u8 val;

	dprintk("\n");
	*status = 0;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	val = mb86a20s_readreg(state, 0x0a) & 0xf;
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	if (val >= 2)
		*status |= FE_HAS_SIGNAL;

	if (val >= 4)
		*status |= FE_HAS_CARRIER;

	if (val >= 5)
		*status |= FE_HAS_VITERBI;

	if (val >= 7)
		*status |= FE_HAS_SYNC;

	if (val >= 8)				/* Maybe 9? */
		*status |= FE_HAS_LOCK;

	dprintk("val = %d, status = 0x%02x\n", val, *status);

	return 0;
}