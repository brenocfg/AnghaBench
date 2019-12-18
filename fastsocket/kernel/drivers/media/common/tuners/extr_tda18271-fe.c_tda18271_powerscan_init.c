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
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 size_t R_EB18 ; 
 size_t R_EB21 ; 
 size_t R_EB23 ; 
 size_t R_EP3 ; 
 size_t R_EP4 ; 
 int tda18271_write_regs (struct dvb_frontend*,size_t,int) ; 
 scalar_t__ tda_fail (int) ; 

__attribute__((used)) static int tda18271_powerscan_init(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int ret;

	/* set standard to digital */
	regs[R_EP3]  &= ~0x1f; /* clear std bits */
	regs[R_EP3]  |= 0x12;

	/* set cal mode to normal */
	regs[R_EP4]  &= ~0x03;

	/* update IF output level */
	regs[R_EP4]  &= ~0x1c; /* clear if level bits */

	ret = tda18271_write_regs(fe, R_EP3, 2);
	if (tda_fail(ret))
		goto fail;

	regs[R_EB18] &= ~0x03; /* set agc1_gain to   6 dB */
	ret = tda18271_write_regs(fe, R_EB18, 1);
	if (tda_fail(ret))
		goto fail;

	regs[R_EB21] &= ~0x03; /* set agc2_gain to -15 dB */

	/* 1.5 MHz low pass filter */
	regs[R_EB23] |= 0x04; /* forcelp_fc2_en = 1 */
	regs[R_EB23] |= 0x02; /* lp_fc[2] = 1 */

	ret = tda18271_write_regs(fe, R_EB21, 3);
fail:
	return ret;
}