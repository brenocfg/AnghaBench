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
struct tuner_simple_priv {int type; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
#define  TUNER_LG_NTSC_TAPE 143 
#define  TUNER_LG_PAL_FM 142 
#define  TUNER_MICROTUNE_4049FM5 141 
#define  TUNER_PHILIPS_FM1216ME_MK3 140 
#define  TUNER_PHILIPS_FM1216MK5 139 
#define  TUNER_PHILIPS_FM1236_MK3 138 
#define  TUNER_PHILIPS_FM1256_IH3 137 
#define  TUNER_PHILIPS_FMD1216MEX_MK3 136 
#define  TUNER_PHILIPS_FMD1216ME_MK3 135 
#define  TUNER_PHILIPS_FQ1216LME_MK3 134 
#define  TUNER_PHILIPS_FQ1236_MK5 133 
#define  TUNER_TCL_MF02GIP_5N 132 
#define  TUNER_TENA_9533_DI 131 
#define  TUNER_THOMSON_DTT761X 130 
#define  TUNER_TNF_5335MF 129 
#define  TUNER_YMEC_TVF_5533MF 128 
 int /*<<< orphan*/  tuner_dbg (char*) ; 
 int /*<<< orphan*/  tuner_err (char*) ; 

__attribute__((used)) static int simple_radio_bandswitch(struct dvb_frontend *fe, u8 *buffer)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;

	switch (priv->type) {
	case TUNER_TENA_9533_DI:
	case TUNER_YMEC_TVF_5533MF:
		tuner_dbg("This tuner doesn't have FM. "
			  "Most cards have a TEA5767 for FM\n");
		return 0;
	case TUNER_PHILIPS_FM1216ME_MK3:
	case TUNER_PHILIPS_FM1236_MK3:
	case TUNER_PHILIPS_FMD1216ME_MK3:
	case TUNER_PHILIPS_FMD1216MEX_MK3:
	case TUNER_LG_NTSC_TAPE:
	case TUNER_PHILIPS_FM1256_IH3:
	case TUNER_TCL_MF02GIP_5N:
		buffer[3] = 0x19;
		break;
	case TUNER_PHILIPS_FM1216MK5:
		buffer[2] = 0x88;
		buffer[3] = 0x09;
		break;
	case TUNER_TNF_5335MF:
		buffer[3] = 0x11;
		break;
	case TUNER_LG_PAL_FM:
		buffer[3] = 0xa5;
		break;
	case TUNER_THOMSON_DTT761X:
		buffer[3] = 0x39;
		break;
	case TUNER_PHILIPS_FQ1216LME_MK3:
	case TUNER_PHILIPS_FQ1236_MK5:
		tuner_err("This tuner doesn't have FM\n");
		/* Set the low band for sanity, since it covers 88-108 MHz */
		buffer[3] = 0x01;
		break;
	case TUNER_MICROTUNE_4049FM5:
	default:
		buffer[3] = 0xa4;
		break;
	}

	return 0;
}