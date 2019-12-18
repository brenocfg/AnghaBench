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
typedef  int u32 ;
struct tda18271_priv {unsigned char* tda18271_regs; int mode; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_PLL ; 
 size_t R_MD1 ; 
 size_t R_MD2 ; 
 size_t R_MD3 ; 
 size_t R_MPD ; 
#define  TDA18271_ANALOG 129 
#define  TDA18271_DIGITAL 128 
 int tda18271_lookup_pll_map (struct dvb_frontend*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ tda_fail (int) ; 

int tda18271_calc_main_pll(struct dvb_frontend *fe, u32 freq)
{
	/* sets main post divider & divider bytes, but does not write them */
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	u8 d, pd;
	u32 div;

	int ret = tda18271_lookup_pll_map(fe, MAIN_PLL, &freq, &pd, &d);
	if (tda_fail(ret))
		goto fail;

	regs[R_MPD]   = (0x77 & pd);

	switch (priv->mode) {
	case TDA18271_ANALOG:
		regs[R_MPD]  &= ~0x08;
		break;
	case TDA18271_DIGITAL:
		regs[R_MPD]  |=  0x08;
		break;
	}

	div =  ((d * (freq / 1000)) << 7) / 125;

	regs[R_MD1]   = 0x7f & (div >> 16);
	regs[R_MD2]   = 0xff & (div >> 8);
	regs[R_MD3]   = 0xff & div;
fail:
	return ret;
}