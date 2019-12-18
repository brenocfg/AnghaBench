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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct lgs8gxx_state {TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ if_clk_freq; scalar_t__ prod; } ;

/* Variables and functions */
 scalar_t__ LGS8GXX_PROD_LGS8G75 ; 
 int /*<<< orphan*/  do_div (int,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  lgs8gxx_write_reg (struct lgs8gxx_state*,int,int) ; 

__attribute__((used)) static int lgs8gxx_set_if_freq(struct lgs8gxx_state *priv, u32 freq /*in kHz*/)
{
	u64 val;
	u32 v32;
	u32 if_clk;

	if_clk = priv->config->if_clk_freq;

	val = freq;
	if (freq != 0) {
		val <<= 32;
		if (if_clk != 0)
			do_div(val, if_clk);
		v32 = val & 0xFFFFFFFF;
		dprintk("Set IF Freq to %dkHz\n", freq);
	} else {
		v32 = 0;
		dprintk("Set IF Freq to baseband\n");
	}
	dprintk("AFC_INIT_FREQ = 0x%08X\n", v32);

	if (priv->config->prod == LGS8GXX_PROD_LGS8G75) {
		lgs8gxx_write_reg(priv, 0x08, 0xFF & (v32));
		lgs8gxx_write_reg(priv, 0x09, 0xFF & (v32 >> 8));
		lgs8gxx_write_reg(priv, 0x0A, 0xFF & (v32 >> 16));
		lgs8gxx_write_reg(priv, 0x0B, 0xFF & (v32 >> 24));
	} else {
		lgs8gxx_write_reg(priv, 0x09, 0xFF & (v32));
		lgs8gxx_write_reg(priv, 0x0A, 0xFF & (v32 >> 8));
		lgs8gxx_write_reg(priv, 0x0B, 0xFF & (v32 >> 16));
		lgs8gxx_write_reg(priv, 0x0C, 0xFF & (v32 >> 24));
	}

	return 0;
}