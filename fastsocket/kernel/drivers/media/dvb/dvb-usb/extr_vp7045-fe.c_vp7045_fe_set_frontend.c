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
typedef  int u32 ;
struct vp7045_fe_state {int /*<<< orphan*/  d; } ;
struct TYPE_3__ {int bandwidth; } ;
struct TYPE_4__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_2__ u; } ;
struct dvb_frontend {struct vp7045_fe_state* demodulator_priv; } ;

/* Variables and functions */
#define  BANDWIDTH_6_MHZ 131 
#define  BANDWIDTH_7_MHZ 130 
#define  BANDWIDTH_8_MHZ 129 
#define  BANDWIDTH_AUTO 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LOCK_TUNER_COMMAND ; 
 int /*<<< orphan*/  vp7045_usb_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vp7045_fe_set_frontend(struct dvb_frontend* fe,
				  struct dvb_frontend_parameters *fep)
{
	struct vp7045_fe_state *state = fe->demodulator_priv;
	u8 buf[5];
	u32 freq = fep->frequency / 1000;

	buf[0] = (freq >> 16) & 0xff;
	buf[1] = (freq >>  8) & 0xff;
	buf[2] =  freq        & 0xff;
	buf[3] = 0;

	switch (fep->u.ofdm.bandwidth) {
		case BANDWIDTH_8_MHZ: buf[4] = 8; break;
		case BANDWIDTH_7_MHZ: buf[4] = 7; break;
		case BANDWIDTH_6_MHZ: buf[4] = 6; break;
		case BANDWIDTH_AUTO: return -EOPNOTSUPP;
		default:
			return -EINVAL;
	}

	vp7045_usb_op(state->d,LOCK_TUNER_COMMAND,buf,5,NULL,0,200);
	return 0;
}