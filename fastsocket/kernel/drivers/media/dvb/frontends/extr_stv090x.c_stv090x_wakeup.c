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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {scalar_t__ device; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1_PON_FIELD ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  STANDBY_FIELD ; 
 scalar_t__ STV0900 ; 
 int /*<<< orphan*/  STV090x_SETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STV090x_SYNTCTRL ; 
 int /*<<< orphan*/  STV090x_TSTTNR1 ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stv090x_read_reg (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stv090x_write_reg (struct stv090x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv090x_wakeup(struct dvb_frontend *fe)
{
	struct stv090x_state *state = fe->demodulator_priv;
	u32 reg;

	dprintk(FE_DEBUG, 1, "Wake %s from standby",
		state->device == STV0900 ? "STV0900" : "STV0903");

	reg = stv090x_read_reg(state, STV090x_SYNTCTRL);
	STV090x_SETFIELD(reg, STANDBY_FIELD, 0x00);
	if (stv090x_write_reg(state, STV090x_SYNTCTRL, reg) < 0)
		goto err;

	reg = stv090x_read_reg(state, STV090x_TSTTNR1);
	STV090x_SETFIELD(reg, ADC1_PON_FIELD, 1);
	if (stv090x_write_reg(state, STV090x_TSTTNR1, reg) < 0)
		goto err;

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}