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
struct stb0899_state {int rx_freq; } ;
struct dvb_diseqc_master_cmd {int* msg; int msg_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQCRESET ; 
 int /*<<< orphan*/  ONECHIP_TRX ; 
 int /*<<< orphan*/  STB0899_DISCNTRL1 ; 
 int /*<<< orphan*/  STB0899_DISCNTRL2 ; 
 int /*<<< orphan*/  STB0899_DISF22 ; 
 int /*<<< orphan*/  STB0899_SETFIELD_VAL (int /*<<< orphan*/ ,int,int) ; 
 int stb0899_get_mclk (struct stb0899_state*) ; 
 int stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stb0899_diseqc_init(struct stb0899_state *state)
{
	struct dvb_diseqc_master_cmd tx_data;
/*
	struct dvb_diseqc_slave_reply rx_data;
*/
	u8 f22_tx, f22_rx, reg;

	u32 mclk, tx_freq = 22000;/* count = 0, i; */
	tx_data.msg[0] = 0xe2;
	tx_data.msg_len = 3;
	reg = stb0899_read_reg(state, STB0899_DISCNTRL2);
	STB0899_SETFIELD_VAL(ONECHIP_TRX, reg, 0);
	stb0899_write_reg(state, STB0899_DISCNTRL2, reg);

	/* disable Tx spy	*/
	reg = stb0899_read_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISEQCRESET, reg, 1);
	stb0899_write_reg(state, STB0899_DISCNTRL1, reg);

	reg = stb0899_read_reg(state, STB0899_DISCNTRL1);
	STB0899_SETFIELD_VAL(DISEQCRESET, reg, 0);
	stb0899_write_reg(state, STB0899_DISCNTRL1, reg);

	mclk = stb0899_get_mclk(state);
	f22_tx = mclk / (tx_freq * 32);
	stb0899_write_reg(state, STB0899_DISF22, f22_tx); /* DiSEqC Tx freq	*/
	state->rx_freq = 20000;
	f22_rx = mclk / (state->rx_freq * 32);

	return 0;
}