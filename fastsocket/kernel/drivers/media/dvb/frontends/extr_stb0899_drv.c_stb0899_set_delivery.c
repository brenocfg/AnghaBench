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
struct stb0899_state {int delsys; int /*<<< orphan*/  verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  FECM_RSVD0 ; 
 int /*<<< orphan*/  FECM_VITERBI_ON ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FRESLDPC ; 
 int /*<<< orphan*/  STB0899_FECM ; 
 int /*<<< orphan*/  STB0899_RSLLC ; 
 int /*<<< orphan*/  STB0899_RSULC ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  STB0899_STOPCLK1 ; 
 int /*<<< orphan*/  STB0899_STOPCLK2 ; 
 int /*<<< orphan*/  STB0899_TSLPL ; 
 int /*<<< orphan*/  STB0899_TSTRES ; 
 int /*<<< orphan*/  STB0899_TSULC ; 
 int /*<<< orphan*/  STOP_CHK8PSK ; 
 int /*<<< orphan*/  STOP_CKADCI108 ; 
 int /*<<< orphan*/  STOP_CKCORE216 ; 
 int /*<<< orphan*/  STOP_CKFEC108 ; 
 int /*<<< orphan*/  STOP_CKFEC216 ; 
 int /*<<< orphan*/  STOP_CKINTBUF216 ; 
 int /*<<< orphan*/  STOP_CKPKDLIN108 ; 
 int /*<<< orphan*/  STOP_CKPKDLIN216 ; 
 int /*<<< orphan*/  STOP_CKS2DMD108 ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb0899_write_regs (struct stb0899_state*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void stb0899_set_delivery(struct stb0899_state *state)
{
	u8 reg;
	u8 stop_clk[2];

	stop_clk[0] = stb0899_read_reg(state, STB0899_STOPCLK1);
	stop_clk[1] = stb0899_read_reg(state, STB0899_STOPCLK2);

	switch (state->delsys) {
	case SYS_DVBS:
		dprintk(state->verbose, FE_DEBUG, 1, "Delivery System -- DVB-S");
		/* FECM/Viterbi ON	*/
		reg = stb0899_read_reg(state, STB0899_FECM);
		STB0899_SETFIELD_VAL(FECM_RSVD0, reg, 0);
		STB0899_SETFIELD_VAL(FECM_VITERBI_ON, reg, 1);
		stb0899_write_reg(state, STB0899_FECM, reg);

		stb0899_write_reg(state, STB0899_RSULC, 0xb1);
		stb0899_write_reg(state, STB0899_TSULC, 0x40);
		stb0899_write_reg(state, STB0899_RSLLC, 0x42);
		stb0899_write_reg(state, STB0899_TSLPL, 0x12);

		reg = stb0899_read_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESLDPC, reg, 1);
		stb0899_write_reg(state, STB0899_TSTRES, reg);

		STB0899_SETFIELD_VAL(STOP_CHK8PSK, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC108, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC216, stop_clk[0], 1);

		STB0899_SETFIELD_VAL(STOP_CKPKDLIN108, stop_clk[1], 1);
		STB0899_SETFIELD_VAL(STOP_CKPKDLIN216, stop_clk[1], 1);

		STB0899_SETFIELD_VAL(STOP_CKINTBUF216, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKCORE216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKS2DMD108, stop_clk[1], 1);
		break;
	case SYS_DVBS2:
		/* FECM/Viterbi OFF	*/
		reg = stb0899_read_reg(state, STB0899_FECM);
		STB0899_SETFIELD_VAL(FECM_RSVD0, reg, 0);
		STB0899_SETFIELD_VAL(FECM_VITERBI_ON, reg, 0);
		stb0899_write_reg(state, STB0899_FECM, reg);

		stb0899_write_reg(state, STB0899_RSULC, 0xb1);
		stb0899_write_reg(state, STB0899_TSULC, 0x42);
		stb0899_write_reg(state, STB0899_RSLLC, 0x40);
		stb0899_write_reg(state, STB0899_TSLPL, 0x02);

		reg = stb0899_read_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESLDPC, reg, 0);
		stb0899_write_reg(state, STB0899_TSTRES, reg);

		STB0899_SETFIELD_VAL(STOP_CHK8PSK, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC108, stop_clk[0], 0);
		STB0899_SETFIELD_VAL(STOP_CKFEC216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKPKDLIN108, stop_clk[1], 0);
		STB0899_SETFIELD_VAL(STOP_CKPKDLIN216, stop_clk[1], 0);

		STB0899_SETFIELD_VAL(STOP_CKINTBUF216, stop_clk[0], 0);
		STB0899_SETFIELD_VAL(STOP_CKCORE216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKS2DMD108, stop_clk[1], 0);
		break;
	case SYS_DSS:
		/* FECM/Viterbi ON	*/
		reg = stb0899_read_reg(state, STB0899_FECM);
		STB0899_SETFIELD_VAL(FECM_RSVD0, reg, 1);
		STB0899_SETFIELD_VAL(FECM_VITERBI_ON, reg, 1);
		stb0899_write_reg(state, STB0899_FECM, reg);

		stb0899_write_reg(state, STB0899_RSULC, 0xa1);
		stb0899_write_reg(state, STB0899_TSULC, 0x61);
		stb0899_write_reg(state, STB0899_RSLLC, 0x42);

		reg = stb0899_read_reg(state, STB0899_TSTRES);
		STB0899_SETFIELD_VAL(FRESLDPC, reg, 1);
		stb0899_write_reg(state, STB0899_TSTRES, reg);

		STB0899_SETFIELD_VAL(STOP_CHK8PSK, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC108, stop_clk[0], 1);
		STB0899_SETFIELD_VAL(STOP_CKFEC216, stop_clk[0], 1);

		STB0899_SETFIELD_VAL(STOP_CKPKDLIN108, stop_clk[1], 1);
		STB0899_SETFIELD_VAL(STOP_CKPKDLIN216, stop_clk[1], 1);

		STB0899_SETFIELD_VAL(STOP_CKCORE216, stop_clk[0], 0);

		STB0899_SETFIELD_VAL(STOP_CKS2DMD108, stop_clk[1], 1);
		break;
	default:
		dprintk(state->verbose, FE_ERROR, 1, "Unsupported delivery system");
		break;
	}
	STB0899_SETFIELD_VAL(STOP_CKADCI108, stop_clk[0], 0);
	stb0899_write_regs(state, STB0899_STOPCLK1, stop_clk, 2);
}