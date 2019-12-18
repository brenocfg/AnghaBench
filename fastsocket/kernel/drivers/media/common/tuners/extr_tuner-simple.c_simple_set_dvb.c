#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tuner_simple_priv {int type; size_t nr; } ;
struct TYPE_5__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_4__ {int /*<<< orphan*/  bandwidth; } ;
struct TYPE_6__ {TYPE_2__ vsb; TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
#define  QAM_256 135 
#define  QAM_64 134 
#define  TUNER_PHILIPS_FCV1236D 133 
#define  TUNER_PHILIPS_FMD1216MEX_MK3 132 
#define  TUNER_PHILIPS_FMD1216ME_MK3 131 
#define  TUNER_PHILIPS_TD1316 130 
#define  TUNER_PHILIPS_TUV1236D 129 
#define  VSB_8 128 
 unsigned int* dtv_input ; 
 int /*<<< orphan*/  simple_set_rf_input (struct dvb_frontend*,int*,int*,unsigned int) ; 

__attribute__((used)) static void simple_set_dvb(struct dvb_frontend *fe, u8 *buf,
			   const struct dvb_frontend_parameters *params)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;

	switch (priv->type) {
	case TUNER_PHILIPS_FMD1216ME_MK3:
	case TUNER_PHILIPS_FMD1216MEX_MK3:
		if (params->u.ofdm.bandwidth == BANDWIDTH_8_MHZ &&
		    params->frequency >= 158870000)
			buf[3] |= 0x08;
		break;
	case TUNER_PHILIPS_TD1316:
		/* determine band */
		buf[3] |= (params->frequency < 161000000) ? 1 :
			  (params->frequency < 444000000) ? 2 : 4;

		/* setup PLL filter */
		if (params->u.ofdm.bandwidth == BANDWIDTH_8_MHZ)
			buf[3] |= 1 << 3;
		break;
	case TUNER_PHILIPS_TUV1236D:
	case TUNER_PHILIPS_FCV1236D:
	{
		unsigned int new_rf;

		if (dtv_input[priv->nr])
			new_rf = dtv_input[priv->nr];
		else
			switch (params->u.vsb.modulation) {
			case QAM_64:
			case QAM_256:
				new_rf = 1;
				break;
			case VSB_8:
			default:
				new_rf = 0;
				break;
			}
		simple_set_rf_input(fe, &buf[2], &buf[3], new_rf);
		break;
	}
	default:
		break;
	}
}