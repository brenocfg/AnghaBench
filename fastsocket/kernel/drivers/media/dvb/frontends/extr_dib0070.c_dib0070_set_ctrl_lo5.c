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
typedef  int u16 ;
struct dvb_frontend {struct dib0070_state* tuner_priv; } ;
struct dib0070_state {int dummy; } ;

/* Variables and functions */
 int dib0070_write_reg (struct dib0070_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int dib0070_set_ctrl_lo5(struct dvb_frontend *fe, u8 vco_bias_trim, u8 hf_div_trim, u8 cp_current, u8 third_order_filt)
{
	struct dib0070_state *state = fe->tuner_priv;
    u16 lo5 = (third_order_filt << 14) | (0 << 13) | (1 << 12) | (3 << 9) | (cp_current << 6) | (hf_div_trim << 3) | (vco_bias_trim << 0);
	dprintk("CTRL_LO5: 0x%x", lo5);
	return dib0070_write_reg(state, 0x15, lo5);
}