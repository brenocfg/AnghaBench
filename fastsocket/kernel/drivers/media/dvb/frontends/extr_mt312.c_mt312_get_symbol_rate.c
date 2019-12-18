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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct mt312_state {int xtal; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MONITOR_H ; 
 int /*<<< orphan*/  MON_CTRL ; 
 int /*<<< orphan*/  SYM_RATE_H ; 
 int /*<<< orphan*/  SYM_RAT_OP_H ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int mt312_div (int,int) ; 
 int mt312_read (struct mt312_state*,int /*<<< orphan*/ ,int*,int) ; 
 int mt312_readreg (struct mt312_state*,int /*<<< orphan*/ ,int*) ; 
 int mt312_writereg (struct mt312_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt312_get_symbol_rate(struct mt312_state *state, u32 *sr)
{
	int ret;
	u8 sym_rate_h;
	u8 dec_ratio;
	u16 sym_rat_op;
	u16 monitor;
	u8 buf[2];

	ret = mt312_readreg(state, SYM_RATE_H, &sym_rate_h);
	if (ret < 0)
		return ret;

	if (sym_rate_h & 0x80) {
		/* symbol rate search was used */
		ret = mt312_writereg(state, MON_CTRL, 0x03);
		if (ret < 0)
			return ret;

		ret = mt312_read(state, MONITOR_H, buf, sizeof(buf));
		if (ret < 0)
			return ret;

		monitor = (buf[0] << 8) | buf[1];

		dprintk("sr(auto) = %u\n",
		       mt312_div(monitor * 15625, 4));
	} else {
		ret = mt312_writereg(state, MON_CTRL, 0x05);
		if (ret < 0)
			return ret;

		ret = mt312_read(state, MONITOR_H, buf, sizeof(buf));
		if (ret < 0)
			return ret;

		dec_ratio = ((buf[0] >> 5) & 0x07) * 32;

		ret = mt312_read(state, SYM_RAT_OP_H, buf, sizeof(buf));
		if (ret < 0)
			return ret;

		sym_rat_op = (buf[0] << 8) | buf[1];

		dprintk("sym_rat_op=%d dec_ratio=%d\n",
		       sym_rat_op, dec_ratio);
		dprintk("*sr(manual) = %lu\n",
		       (((state->xtal * 8192) / (sym_rat_op + 8192)) *
			2) - dec_ratio);
	}

	return 0;
}