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
struct mt312_state {int id; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPP_CTRL ; 
#define  ID_ZL10313 128 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt312_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct mt312_state *state = fe->demodulator_priv;

	u8 val = 0x00;
	int ret;

	switch (state->id) {
	case ID_ZL10313:
		ret = mt312_readreg(state, GPP_CTRL, &val);
		if (ret < 0)
			goto error;

		/* preserve this bit to not accidently shutdown ADC */
		val &= 0x80;
		break;
	}

	if (enable)
		val |= 0x40;
	else
		val &= ~0x40;

	ret = mt312_writereg(state, GPP_CTRL, val);

error:
	return ret;
}