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
struct mt312_state {scalar_t__ id; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 int /*<<< orphan*/  GPP_CTRL ; 
 int /*<<< orphan*/  HW_CTRL ; 
 scalar_t__ ID_ZL10313 ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 
 int mt312_reset (struct mt312_state*,int) ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt312_sleep(struct dvb_frontend *fe)
{
	struct mt312_state *state = fe->demodulator_priv;
	int ret;
	u8 config;

	/* reset all registers to defaults */
	ret = mt312_reset(state, 1);
	if (ret < 0)
		return ret;

	if (state->id == ID_ZL10313) {
		/* reset ADC */
		ret = mt312_writereg(state, GPP_CTRL, 0x00);
		if (ret < 0)
			return ret;

		/* full shutdown of ADCs, mpeg bus tristated */
		ret = mt312_writereg(state, HW_CTRL, 0x0d);
		if (ret < 0)
			return ret;
	}

	ret = mt312_readreg(state, CONFIG, &config);
	if (ret < 0)
		return ret;

	/* enter standby */
	ret = mt312_writereg(state, CONFIG, config & 0x7f);
	if (ret < 0)
		return ret;

	return 0;
}