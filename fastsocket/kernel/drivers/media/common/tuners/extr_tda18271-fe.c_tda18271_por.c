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
 size_t R_EB12 ; 
 size_t R_EB18 ; 
 size_t R_EB21 ; 
 size_t R_EB23 ; 
 int tda18271_set_standby_mode (struct dvb_frontend*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tda18271_write_regs (struct dvb_frontend*,size_t,int) ; 
 scalar_t__ tda_fail (int) ; 

__attribute__((used)) static int tda18271_por(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int ret;

	/* power up detector 1 */
	regs[R_EB12] &= ~0x20;
	ret = tda18271_write_regs(fe, R_EB12, 1);
	if (tda_fail(ret))
		goto fail;

	regs[R_EB18] &= ~0x80; /* turn agc1 loop on */
	regs[R_EB18] &= ~0x03; /* set agc1_gain to  6 dB */
	ret = tda18271_write_regs(fe, R_EB18, 1);
	if (tda_fail(ret))
		goto fail;

	regs[R_EB21] |= 0x03; /* set agc2_gain to -6 dB */

	/* POR mode */
	ret = tda18271_set_standby_mode(fe, 1, 0, 0);
	if (tda_fail(ret))
		goto fail;

	/* disable 1.5 MHz low pass filter */
	regs[R_EB23] &= ~0x04; /* forcelp_fc2_en = 0 */
	regs[R_EB23] &= ~0x02; /* XXX: lp_fc[2] = 0 */
	ret = tda18271_write_regs(fe, R_EB21, 3);
fail:
	return ret;
}