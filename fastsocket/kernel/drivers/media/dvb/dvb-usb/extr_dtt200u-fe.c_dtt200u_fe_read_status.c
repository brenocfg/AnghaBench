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
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int /*<<< orphan*/  d; } ;
typedef  int fe_status_t ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int FE_TIMEDOUT ; 
 int GET_TUNE_STATUS ; 
 int /*<<< orphan*/  dvb_usb_generic_rw (int /*<<< orphan*/ ,int*,int,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dtt200u_fe_read_status(struct dvb_frontend* fe, fe_status_t *stat)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	u8 st = GET_TUNE_STATUS, b[3];

	dvb_usb_generic_rw(state->d,&st,1,b,3,0);

	switch (b[0]) {
		case 0x01:
			*stat = FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
			break;
		case 0x00: /* pending */
			*stat = FE_TIMEDOUT; /* during set_frontend */
			break;
		default:
		case 0x02: /* failed */
			*stat = 0;
			break;
	}
	return 0;
}