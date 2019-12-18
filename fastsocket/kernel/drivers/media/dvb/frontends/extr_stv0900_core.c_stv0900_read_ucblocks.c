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
typedef  int u32 ;
struct stv0900_state {int demod; struct stv0900_internal* internal; } ;
struct stv0900_internal {int dummy; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;

/* Variables and functions */
 int /*<<< orphan*/  BBFCRCKO0 ; 
 int /*<<< orphan*/  BBFCRCKO1 ; 
 scalar_t__ STV0900_DVBS2_STANDARD ; 
 int /*<<< orphan*/  UPCRCKO0 ; 
 int /*<<< orphan*/  UPCRCKO1 ; 
 scalar_t__ stv0900_get_standard (struct dvb_frontend*,int) ; 
 int stv0900_read_reg (struct stv0900_internal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0900_read_ucblocks(struct dvb_frontend *fe, u32 * ucblocks)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;
	u8 err_val1, err_val0;
	u32 header_err_val = 0;

	*ucblocks = 0x0;
	if (stv0900_get_standard(fe, demod) == STV0900_DVBS2_STANDARD) {
		/* DVB-S2 delineator errors count */

		/* retreiving number for errnous headers */
		err_val1 = stv0900_read_reg(intp, BBFCRCKO1);
		err_val0 = stv0900_read_reg(intp, BBFCRCKO0);
		header_err_val = (err_val1 << 8) | err_val0;

		/* retreiving number for errnous packets */
		err_val1 = stv0900_read_reg(intp, UPCRCKO1);
		err_val0 = stv0900_read_reg(intp, UPCRCKO0);
		*ucblocks = (err_val1 << 8) | err_val0;
		*ucblocks += header_err_val;
	}

	return 0;
}