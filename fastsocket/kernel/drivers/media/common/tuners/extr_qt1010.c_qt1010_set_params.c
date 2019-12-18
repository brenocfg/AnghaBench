#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct qt1010_priv {int frequency; int reg1f_init_val; int reg20_init_val; int reg25_init_val; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_8__ {int /*<<< orphan*/  bandwidth; } ;
struct TYPE_9__ {TYPE_2__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__ info; } ;
struct dvb_frontend {TYPE_4__ ops; struct qt1010_priv* tuner_priv; } ;
struct TYPE_11__ {scalar_t__ member_0; int member_1; int member_2; int val; scalar_t__ oper; int /*<<< orphan*/  reg; } ;
typedef  TYPE_5__ qt1010_i2c_oper_t ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 scalar_t__ FE_OFDM ; 
 int FREQ1 ; 
 int FREQ2 ; 
 int QT1010_OFFSET ; 
 scalar_t__ QT1010_RD ; 
 int QT1010_STEP ; 
 scalar_t__ QT1010_WR ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dprintk (char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  qt1010_dump_regs (struct qt1010_priv*) ; 
 int qt1010_readreg (struct qt1010_priv*,int /*<<< orphan*/ ,int*) ; 
 int qt1010_writereg (struct qt1010_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int qt1010_set_params(struct dvb_frontend *fe,
			     struct dvb_frontend_parameters *params)
{
	struct qt1010_priv *priv;
	int err;
	u32 freq, div, mod1, mod2;
	u8 i, tmpval, reg05;
	qt1010_i2c_oper_t rd[48] = {
		{ QT1010_WR, 0x01, 0x80 },
		{ QT1010_WR, 0x02, 0x3f },
		{ QT1010_WR, 0x05, 0xff }, /* 02 c write */
		{ QT1010_WR, 0x06, 0x44 },
		{ QT1010_WR, 0x07, 0xff }, /* 04 c write */
		{ QT1010_WR, 0x08, 0x08 },
		{ QT1010_WR, 0x09, 0xff }, /* 06 c write */
		{ QT1010_WR, 0x0a, 0xff }, /* 07 c write */
		{ QT1010_WR, 0x0b, 0xff }, /* 08 c write */
		{ QT1010_WR, 0x0c, 0xe1 },
		{ QT1010_WR, 0x1a, 0xff }, /* 10 c write */
		{ QT1010_WR, 0x1b, 0x00 },
		{ QT1010_WR, 0x1c, 0x89 },
		{ QT1010_WR, 0x11, 0xff }, /* 13 c write */
		{ QT1010_WR, 0x12, 0xff }, /* 14 c write */
		{ QT1010_WR, 0x22, 0xff }, /* 15 c write */
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x1e, 0xd0 },
		{ QT1010_RD, 0x22, 0xff }, /* 16 c read */
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_RD, 0x05, 0xff }, /* 20 c read */
		{ QT1010_RD, 0x22, 0xff }, /* 21 c read */
		{ QT1010_WR, 0x23, 0xd0 },
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x1e, 0xe0 },
		{ QT1010_RD, 0x23, 0xff }, /* 25 c read */
		{ QT1010_RD, 0x23, 0xff }, /* 26 c read */
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x24, 0xd0 },
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x1e, 0xf0 },
		{ QT1010_RD, 0x24, 0xff }, /* 31 c read */
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x14, 0x7f },
		{ QT1010_WR, 0x15, 0x7f },
		{ QT1010_WR, 0x05, 0xff }, /* 35 c write */
		{ QT1010_WR, 0x06, 0x00 },
		{ QT1010_WR, 0x15, 0x1f },
		{ QT1010_WR, 0x16, 0xff },
		{ QT1010_WR, 0x18, 0xff },
		{ QT1010_WR, 0x1f, 0xff }, /* 40 c write */
		{ QT1010_WR, 0x20, 0xff }, /* 41 c write */
		{ QT1010_WR, 0x21, 0x53 },
		{ QT1010_WR, 0x25, 0xff }, /* 43 c write */
		{ QT1010_WR, 0x26, 0x15 },
		{ QT1010_WR, 0x00, 0xff }, /* 45 c write */
		{ QT1010_WR, 0x02, 0x00 },
		{ QT1010_WR, 0x01, 0x00 }
	};

#define FREQ1 32000000 /* 32 MHz */
#define FREQ2  4000000 /* 4 MHz Quartz oscillator in the stick? */

	priv = fe->tuner_priv;
	freq = params->frequency;
	div = (freq + QT1010_OFFSET) / QT1010_STEP;
	freq = (div * QT1010_STEP) - QT1010_OFFSET;
	mod1 = (freq + QT1010_OFFSET) % FREQ1;
	mod2 = (freq + QT1010_OFFSET) % FREQ2;
	priv->bandwidth =
		(fe->ops.info.type == FE_OFDM) ? params->u.ofdm.bandwidth : 0;
	priv->frequency = freq;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	/* reg 05 base value */
	if      (freq < 290000000) reg05 = 0x14; /* 290 MHz */
	else if (freq < 610000000) reg05 = 0x34; /* 610 MHz */
	else if (freq < 802000000) reg05 = 0x54; /* 802 MHz */
	else                       reg05 = 0x74;

	/* 0x5 */
	rd[2].val = reg05;

	/* 07 - set frequency: 32 MHz scale */
	rd[4].val = (freq + QT1010_OFFSET) / FREQ1;

	/* 09 - changes every 8/24 MHz */
	if (mod1 < 8000000) rd[6].val = 0x1d;
	else                rd[6].val = 0x1c;

	/* 0a - set frequency: 4 MHz scale (max 28 MHz) */
	if      (mod1 < 1*FREQ2) rd[7].val = 0x09; /*  +0 MHz */
	else if (mod1 < 2*FREQ2) rd[7].val = 0x08; /*  +4 MHz */
	else if (mod1 < 3*FREQ2) rd[7].val = 0x0f; /*  +8 MHz */
	else if (mod1 < 4*FREQ2) rd[7].val = 0x0e; /* +12 MHz */
	else if (mod1 < 5*FREQ2) rd[7].val = 0x0d; /* +16 MHz */
	else if (mod1 < 6*FREQ2) rd[7].val = 0x0c; /* +20 MHz */
	else if (mod1 < 7*FREQ2) rd[7].val = 0x0b; /* +24 MHz */
	else                     rd[7].val = 0x0a; /* +28 MHz */

	/* 0b - changes every 2/2 MHz */
	if (mod2 < 2000000) rd[8].val = 0x45;
	else                rd[8].val = 0x44;

	/* 1a - set frequency: 125 kHz scale (max 3875 kHz)*/
	tmpval = 0x78; /* byte, overflows intentionally */
	rd[10].val = tmpval-((mod2/QT1010_STEP)*0x08);

	/* 11 */
	rd[13].val = 0xfd; /* TODO: correct value calculation */

	/* 12 */
	rd[14].val = 0x91; /* TODO: correct value calculation */

	/* 22 */
	if      (freq < 450000000) rd[15].val = 0xd0; /* 450 MHz */
	else if (freq < 482000000) rd[15].val = 0xd1; /* 482 MHz */
	else if (freq < 514000000) rd[15].val = 0xd4; /* 514 MHz */
	else if (freq < 546000000) rd[15].val = 0xd7; /* 546 MHz */
	else if (freq < 610000000) rd[15].val = 0xda; /* 610 MHz */
	else                       rd[15].val = 0xd0;

	/* 05 */
	rd[35].val = (reg05 & 0xf0);

	/* 1f */
	if      (mod1 <  8000000) tmpval = 0x00;
	else if (mod1 < 12000000) tmpval = 0x01;
	else if (mod1 < 16000000) tmpval = 0x02;
	else if (mod1 < 24000000) tmpval = 0x03;
	else if (mod1 < 28000000) tmpval = 0x04;
	else                      tmpval = 0x05;
	rd[40].val = (priv->reg1f_init_val + 0x0e + tmpval);

	/* 20 */
	if      (mod1 <  8000000) tmpval = 0x00;
	else if (mod1 < 12000000) tmpval = 0x01;
	else if (mod1 < 20000000) tmpval = 0x02;
	else if (mod1 < 24000000) tmpval = 0x03;
	else if (mod1 < 28000000) tmpval = 0x04;
	else                      tmpval = 0x05;
	rd[41].val = (priv->reg20_init_val + 0x0d + tmpval);

	/* 25 */
	rd[43].val = priv->reg25_init_val;

	/* 00 */
	rd[45].val = 0x92; /* TODO: correct value calculation */

	dprintk("freq:%u 05:%02x 07:%02x 09:%02x 0a:%02x 0b:%02x " \
		"1a:%02x 11:%02x 12:%02x 22:%02x 05:%02x 1f:%02x " \
		"20:%02x 25:%02x 00:%02x", \
		freq, rd[2].val, rd[4].val, rd[6].val, rd[7].val, rd[8].val, \
		rd[10].val, rd[13].val, rd[14].val, rd[15].val, rd[35].val, \
		rd[40].val, rd[41].val, rd[43].val, rd[45].val);

	for (i = 0; i < ARRAY_SIZE(rd); i++) {
		if (rd[i].oper == QT1010_WR) {
			err = qt1010_writereg(priv, rd[i].reg, rd[i].val);
		} else { /* read is required to proper locking */
			err = qt1010_readreg(priv, rd[i].reg, &tmpval);
		}
		if (err) return err;
	}

	if (debug)
		qt1010_dump_regs(priv);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	return 0;
}