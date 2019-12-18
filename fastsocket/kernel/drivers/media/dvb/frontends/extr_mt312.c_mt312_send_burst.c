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
struct mt312_state {int dummy; } ;
struct dvb_frontend {struct mt312_state* demodulator_priv; } ;
typedef  size_t fe_sec_mini_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQC_MODE ; 
 int EINVAL ; 
 size_t const SEC_MINI_B ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt312_send_burst(struct dvb_frontend *fe, const fe_sec_mini_cmd_t c)
{
	struct mt312_state *state = fe->demodulator_priv;
	const u8 mini_tab[2] = { 0x02, 0x03 };

	int ret;
	u8 diseqc_mode;

	if (c > SEC_MINI_B)
		return -EINVAL;

	ret = mt312_readreg(state, DISEQC_MODE, &diseqc_mode);
	if (ret < 0)
		return ret;

	ret = mt312_writereg(state, DISEQC_MODE,
			     (diseqc_mode & 0x40) | mini_tab[c]);
	if (ret < 0)
		return ret;

	return 0;
}