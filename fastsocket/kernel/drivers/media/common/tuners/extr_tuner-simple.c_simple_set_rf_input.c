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
#define  TUNER_PHILIPS_FCV1236D 129 
#define  TUNER_PHILIPS_TUV1236D 128 

__attribute__((used)) static void simple_set_rf_input(struct dvb_frontend *fe,
				u8 *config, u8 *cb, unsigned int rf)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;

	switch (priv->type) {
	case TUNER_PHILIPS_TUV1236D:
		switch (rf) {
		case 1:
			*cb |= 0x08;
			break;
		default:
			*cb &= ~0x08;
			break;
		}
		break;
	case TUNER_PHILIPS_FCV1236D:
		switch (rf) {
		case 1:
			*cb |= 0x01;
			break;
		default:
			*cb &= ~0x01;
			break;
		}
		break;
	default:
		break;
	}
}