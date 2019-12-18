#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mt2060_priv {int if1_freq; int frequency; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_6__ {int /*<<< orphan*/  bandwidth; } ;
struct TYPE_7__ {TYPE_2__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;TYPE_1__ info; } ;
struct dvb_frontend {TYPE_4__ ops; struct mt2060_priv* tuner_priv; } ;

/* Variables and functions */
 scalar_t__ FE_OFDM ; 
 int FREF ; 
 int IF2 ; 
 int REG_LO1B1 ; 
 int REG_LO1C1 ; 
 int /*<<< orphan*/  REG_LO_STATUS ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt2060_readreg (struct mt2060_priv*,int /*<<< orphan*/ ,int*) ; 
 int mt2060_spurcheck (int,int,int) ; 
 int /*<<< orphan*/  mt2060_writeregs (struct mt2060_priv*,int*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int mt2060_set_params(struct dvb_frontend *fe, struct dvb_frontend_parameters *params)
{
	struct mt2060_priv *priv;
	int ret=0;
	int i=0;
	u32 freq;
	u8  lnaband;
	u32 f_lo1,f_lo2;
	u32 div1,num1,div2,num2;
	u8  b[8];
	u32 if1;

	priv = fe->tuner_priv;

	if1 = priv->if1_freq;
	b[0] = REG_LO1B1;
	b[1] = 0xFF;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	mt2060_writeregs(priv,b,2);

	freq = params->frequency / 1000; // Hz -> kHz
	priv->bandwidth = (fe->ops.info.type == FE_OFDM) ? params->u.ofdm.bandwidth : 0;

	f_lo1 = freq + if1 * 1000;
	f_lo1 = (f_lo1 / 250) * 250;
	f_lo2 = f_lo1 - freq - IF2;
	// From the Comtech datasheet, the step used is 50kHz. The tuner chip could be more precise
	f_lo2 = ((f_lo2 + 25) / 50) * 50;
	priv->frequency =  (f_lo1 - f_lo2 - IF2) * 1000,

#ifdef MT2060_SPURCHECK
	// LO-related spurs detection and correction
	num1   = mt2060_spurcheck(f_lo1,f_lo2,IF2);
	f_lo1 += num1;
	f_lo2 += num1;
#endif
	//Frequency LO1 = 16MHz * (DIV1 + NUM1/64 )
	num1 = f_lo1 / (FREF / 64);
	div1 = num1 / 64;
	num1 &= 0x3f;

	// Frequency LO2 = 16MHz * (DIV2 + NUM2/8192 )
	num2 = f_lo2 * 64 / (FREF / 128);
	div2 = num2 / 8192;
	num2 &= 0x1fff;

	if (freq <=  95000) lnaband = 0xB0; else
	if (freq <= 180000) lnaband = 0xA0; else
	if (freq <= 260000) lnaband = 0x90; else
	if (freq <= 335000) lnaband = 0x80; else
	if (freq <= 425000) lnaband = 0x70; else
	if (freq <= 480000) lnaband = 0x60; else
	if (freq <= 570000) lnaband = 0x50; else
	if (freq <= 645000) lnaband = 0x40; else
	if (freq <= 730000) lnaband = 0x30; else
	if (freq <= 810000) lnaband = 0x20; else lnaband = 0x10;

	b[0] = REG_LO1C1;
	b[1] = lnaband | ((num1 >>2) & 0x0F);
	b[2] = div1;
	b[3] = (num2 & 0x0F)  | ((num1 & 3) << 4);
	b[4] = num2 >> 4;
	b[5] = ((num2 >>12) & 1) | (div2 << 1);

	dprintk("IF1: %dMHz",(int)if1);
	dprintk("PLL freq=%dkHz  f_lo1=%dkHz  f_lo2=%dkHz",(int)freq,(int)f_lo1,(int)f_lo2);
	dprintk("PLL div1=%d  num1=%d  div2=%d  num2=%d",(int)div1,(int)num1,(int)div2,(int)num2);
	dprintk("PLL [1..5]: %2x %2x %2x %2x %2x",(int)b[1],(int)b[2],(int)b[3],(int)b[4],(int)b[5]);

	mt2060_writeregs(priv,b,6);

	//Waits for pll lock or timeout
	i = 0;
	do {
		mt2060_readreg(priv,REG_LO_STATUS,b);
		if ((b[0] & 0x88)==0x88)
			break;
		msleep(4);
		i++;
	} while (i<10);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	return ret;
}