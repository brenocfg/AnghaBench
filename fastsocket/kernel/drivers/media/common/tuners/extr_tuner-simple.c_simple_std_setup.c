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
struct tuner_i2c_props {int addr; } ;
struct tuner_simple_priv {int type; size_t nr; struct tuner_i2c_props i2c_props; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;
struct analog_parameters {int std; } ;

/* Variables and functions */
 int PHILIPS_MF_SET_STD_BG ; 
 int PHILIPS_MF_SET_STD_L ; 
 int PHILIPS_MF_SET_STD_LC ; 
 int PHILIPS_SET_PAL_BGDK ; 
 int PHILIPS_SET_PAL_I ; 
 int PHILIPS_SET_PAL_L ; 
 int TEMIC_SET_PAL_BG ; 
 int TEMIC_SET_PAL_DK ; 
 int TEMIC_SET_PAL_I ; 
 int TEMIC_SET_PAL_L ; 
 int TUNER_CHARGE_PUMP ; 
#define  TUNER_MICROTUNE_4042FI5 133 
#define  TUNER_PHILIPS_FCV1236D 132 
#define  TUNER_PHILIPS_FQ1216ME 131 
#define  TUNER_PHILIPS_SECAM 130 
#define  TUNER_PHILIPS_TUV1236D 129 
#define  TUNER_TEMIC_4046FM5 128 
 int V4L2_STD_ATSC ; 
 int V4L2_STD_PAL_BG ; 
 int V4L2_STD_PAL_DK ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 scalar_t__* atv_input ; 
 int /*<<< orphan*/  simple_set_rf_input (struct dvb_frontend*,int*,int*,scalar_t__) ; 
 int tuner_i2c_xfer_send (struct tuner_i2c_props*,int*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,int) ; 

__attribute__((used)) static int simple_std_setup(struct dvb_frontend *fe,
			    struct analog_parameters *params,
			    u8 *config, u8 *cb)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;
	int rc;

	/* tv norm specific stuff for multi-norm tuners */
	switch (priv->type) {
	case TUNER_PHILIPS_SECAM: /* FI1216MF */
		/* 0x01 -> ??? no change ??? */
		/* 0x02 -> PAL BDGHI / SECAM L */
		/* 0x04 -> ??? PAL others / SECAM others ??? */
		*cb &= ~0x03;
		if (params->std & V4L2_STD_SECAM_L)
			/* also valid for V4L2_STD_SECAM */
			*cb |= PHILIPS_MF_SET_STD_L;
		else if (params->std & V4L2_STD_SECAM_LC)
			*cb |= PHILIPS_MF_SET_STD_LC;
		else /* V4L2_STD_B|V4L2_STD_GH */
			*cb |= PHILIPS_MF_SET_STD_BG;
		break;

	case TUNER_TEMIC_4046FM5:
		*cb &= ~0x0f;

		if (params->std & V4L2_STD_PAL_BG) {
			*cb |= TEMIC_SET_PAL_BG;

		} else if (params->std & V4L2_STD_PAL_I) {
			*cb |= TEMIC_SET_PAL_I;

		} else if (params->std & V4L2_STD_PAL_DK) {
			*cb |= TEMIC_SET_PAL_DK;

		} else if (params->std & V4L2_STD_SECAM_L) {
			*cb |= TEMIC_SET_PAL_L;

		}
		break;

	case TUNER_PHILIPS_FQ1216ME:
		*cb &= ~0x0f;

		if (params->std & (V4L2_STD_PAL_BG|V4L2_STD_PAL_DK)) {
			*cb |= PHILIPS_SET_PAL_BGDK;

		} else if (params->std & V4L2_STD_PAL_I) {
			*cb |= PHILIPS_SET_PAL_I;

		} else if (params->std & V4L2_STD_SECAM_L) {
			*cb |= PHILIPS_SET_PAL_L;

		}
		break;

	case TUNER_PHILIPS_FCV1236D:
		/* 0x00 -> ATSC antenna input 1 */
		/* 0x01 -> ATSC antenna input 2 */
		/* 0x02 -> NTSC antenna input 1 */
		/* 0x03 -> NTSC antenna input 2 */
		*cb &= ~0x03;
		if (!(params->std & V4L2_STD_ATSC))
			*cb |= 2;
		break;

	case TUNER_MICROTUNE_4042FI5:
		/* Set the charge pump for fast tuning */
		*config |= TUNER_CHARGE_PUMP;
		break;

	case TUNER_PHILIPS_TUV1236D:
	{
		struct tuner_i2c_props i2c = priv->i2c_props;
		/* 0x40 -> ATSC antenna input 1 */
		/* 0x48 -> ATSC antenna input 2 */
		/* 0x00 -> NTSC antenna input 1 */
		/* 0x08 -> NTSC antenna input 2 */
		u8 buffer[4] = { 0x14, 0x00, 0x17, 0x00};
		*cb &= ~0x40;
		if (params->std & V4L2_STD_ATSC) {
			*cb |= 0x40;
			buffer[1] = 0x04;
		}
		/* set to the correct mode (analog or digital) */
		i2c.addr = 0x0a;
		rc = tuner_i2c_xfer_send(&i2c, &buffer[0], 2);
		if (2 != rc)
			tuner_warn("i2c i/o error: rc == %d "
				   "(should be 2)\n", rc);
		rc = tuner_i2c_xfer_send(&i2c, &buffer[2], 2);
		if (2 != rc)
			tuner_warn("i2c i/o error: rc == %d "
				   "(should be 2)\n", rc);
		break;
	}
	}
	if (atv_input[priv->nr])
		simple_set_rf_input(fe, config, cb, atv_input[priv->nr]);

	return 0;
}