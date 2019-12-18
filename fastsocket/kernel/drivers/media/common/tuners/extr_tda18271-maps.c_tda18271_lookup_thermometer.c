#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tda18271_priv {unsigned char* tda18271_regs; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;
struct TYPE_2__ {unsigned char d; int r1; int r0; } ;

/* Variables and functions */
 size_t R_TM ; 
 TYPE_1__* tda18271_thermometer ; 
 int /*<<< orphan*/  tda_map (char*,int,int) ; 

int tda18271_lookup_thermometer(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	int val, i = 0;

	while (tda18271_thermometer[i].d < (regs[R_TM] & 0x0f)) {
		if (tda18271_thermometer[i + 1].d == 0)
			break;
		i++;
	}

	if ((regs[R_TM] & 0x20) == 0x20)
		val = tda18271_thermometer[i].r1;
	else
		val = tda18271_thermometer[i].r0;

	tda_map("(%d) tm = %d\n", i, val);

	return val;
}