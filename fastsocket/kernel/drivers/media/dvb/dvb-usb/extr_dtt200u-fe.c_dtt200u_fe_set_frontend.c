#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_3__ {int bandwidth; } ;
struct TYPE_4__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_2__ u; } ;
struct dvb_frontend {struct dtt200u_fe_state* demodulator_priv; } ;
struct dtt200u_fe_state {int /*<<< orphan*/  d; } ;
typedef  int fe_status_t ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 131 
#define  BANDWIDTH_7_MHZ 130 
#define  BANDWIDTH_8_MHZ 129 
#define  BANDWIDTH_AUTO 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int FE_TIMEDOUT ; 
 int SET_BANDWIDTH ; 
 int SET_RF_FREQ ; 
 int /*<<< orphan*/  dtt200u_fe_read_status (struct dvb_frontend*,int*) ; 
 int /*<<< orphan*/  dvb_usb_generic_write (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dtt200u_fe_set_frontend(struct dvb_frontend* fe,
				  struct dvb_frontend_parameters *fep)
{
	struct dtt200u_fe_state *state = fe->demodulator_priv;
	int i;
	fe_status_t st;
	u16 freq = fep->frequency / 250000;
	u8 bwbuf[2] = { SET_BANDWIDTH, 0 },freqbuf[3] = { SET_RF_FREQ, 0, 0 };

	switch (fep->u.ofdm.bandwidth) {
		case BANDWIDTH_8_MHZ: bwbuf[1] = 8; break;
		case BANDWIDTH_7_MHZ: bwbuf[1] = 7; break;
		case BANDWIDTH_6_MHZ: bwbuf[1] = 6; break;
		case BANDWIDTH_AUTO: return -EOPNOTSUPP;
		default:
			return -EINVAL;
	}

	dvb_usb_generic_write(state->d,bwbuf,2);

	freqbuf[1] = freq & 0xff;
	freqbuf[2] = (freq >> 8) & 0xff;
	dvb_usb_generic_write(state->d,freqbuf,3);

	for (i = 0; i < 30; i++) {
		msleep(20);
		dtt200u_fe_read_status(fe, &st);
		if (st & FE_TIMEDOUT)
			continue;
	}

	return 0;
}