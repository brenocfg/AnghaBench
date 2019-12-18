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
struct nxt6000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFDM_COR_STAT ; 
 int /*<<< orphan*/  OFDM_SYR_STAT ; 
 int /*<<< orphan*/  OFDM_TPS_RCVD_3 ; 
 int /*<<< orphan*/  OFDM_TPS_RCVD_4 ; 
 int /*<<< orphan*/  RF_AGC_STATUS ; 
 int /*<<< orphan*/  RF_AGC_VAL_1 ; 
 int /*<<< orphan*/  RS_COR_STAT ; 
 int /*<<< orphan*/  VIT_SYNC_STATUS ; 
 int nxt6000_readreg (struct nxt6000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void nxt6000_dump_status(struct nxt6000_state *state)
{
	u8 val;

/*
	printk("RS_COR_STAT: 0x%02X\n", nxt6000_readreg(fe, RS_COR_STAT));
	printk("VIT_SYNC_STATUS: 0x%02X\n", nxt6000_readreg(fe, VIT_SYNC_STATUS));
	printk("OFDM_COR_STAT: 0x%02X\n", nxt6000_readreg(fe, OFDM_COR_STAT));
	printk("OFDM_SYR_STAT: 0x%02X\n", nxt6000_readreg(fe, OFDM_SYR_STAT));
	printk("OFDM_TPS_RCVD_1: 0x%02X\n", nxt6000_readreg(fe, OFDM_TPS_RCVD_1));
	printk("OFDM_TPS_RCVD_2: 0x%02X\n", nxt6000_readreg(fe, OFDM_TPS_RCVD_2));
	printk("OFDM_TPS_RCVD_3: 0x%02X\n", nxt6000_readreg(fe, OFDM_TPS_RCVD_3));
	printk("OFDM_TPS_RCVD_4: 0x%02X\n", nxt6000_readreg(fe, OFDM_TPS_RCVD_4));
	printk("OFDM_TPS_RESERVED_1: 0x%02X\n", nxt6000_readreg(fe, OFDM_TPS_RESERVED_1));
	printk("OFDM_TPS_RESERVED_2: 0x%02X\n", nxt6000_readreg(fe, OFDM_TPS_RESERVED_2));
*/
	printk("NXT6000 status:");

	val = nxt6000_readreg(state, RS_COR_STAT);

	printk(" DATA DESCR LOCK: %d,", val & 0x01);
	printk(" DATA SYNC LOCK: %d,", (val >> 1) & 0x01);

	val = nxt6000_readreg(state, VIT_SYNC_STATUS);

	printk(" VITERBI LOCK: %d,", (val >> 7) & 0x01);

	switch ((val >> 4) & 0x07) {

	case 0x00:
		printk(" VITERBI CODERATE: 1/2,");
		break;

	case 0x01:
		printk(" VITERBI CODERATE: 2/3,");
		break;

	case 0x02:
		printk(" VITERBI CODERATE: 3/4,");
		break;

	case 0x03:
		printk(" VITERBI CODERATE: 5/6,");
		break;

	case 0x04:
		printk(" VITERBI CODERATE: 7/8,");
		break;

	default:
		printk(" VITERBI CODERATE: Reserved,");

	}

	val = nxt6000_readreg(state, OFDM_COR_STAT);

	printk(" CHCTrack: %d,", (val >> 7) & 0x01);
	printk(" TPSLock: %d,", (val >> 6) & 0x01);
	printk(" SYRLock: %d,", (val >> 5) & 0x01);
	printk(" AGCLock: %d,", (val >> 4) & 0x01);

	switch (val & 0x0F) {

	case 0x00:
		printk(" CoreState: IDLE,");
		break;

	case 0x02:
		printk(" CoreState: WAIT_AGC,");
		break;

	case 0x03:
		printk(" CoreState: WAIT_SYR,");
		break;

	case 0x04:
		printk(" CoreState: WAIT_PPM,");
		break;

	case 0x01:
		printk(" CoreState: WAIT_TRL,");
		break;

	case 0x05:
		printk(" CoreState: WAIT_TPS,");
		break;

	case 0x06:
		printk(" CoreState: MONITOR_TPS,");
		break;

	default:
		printk(" CoreState: Reserved,");

	}

	val = nxt6000_readreg(state, OFDM_SYR_STAT);

	printk(" SYRLock: %d,", (val >> 4) & 0x01);
	printk(" SYRMode: %s,", (val >> 2) & 0x01 ? "8K" : "2K");

	switch ((val >> 4) & 0x03) {

	case 0x00:
		printk(" SYRGuard: 1/32,");
		break;

	case 0x01:
		printk(" SYRGuard: 1/16,");
		break;

	case 0x02:
		printk(" SYRGuard: 1/8,");
		break;

	case 0x03:
		printk(" SYRGuard: 1/4,");
		break;
	}

	val = nxt6000_readreg(state, OFDM_TPS_RCVD_3);

	switch ((val >> 4) & 0x07) {

	case 0x00:
		printk(" TPSLP: 1/2,");
		break;

	case 0x01:
		printk(" TPSLP: 2/3,");
		break;

	case 0x02:
		printk(" TPSLP: 3/4,");
		break;

	case 0x03:
		printk(" TPSLP: 5/6,");
		break;

	case 0x04:
		printk(" TPSLP: 7/8,");
		break;

	default:
		printk(" TPSLP: Reserved,");

	}

	switch (val & 0x07) {

	case 0x00:
		printk(" TPSHP: 1/2,");
		break;

	case 0x01:
		printk(" TPSHP: 2/3,");
		break;

	case 0x02:
		printk(" TPSHP: 3/4,");
		break;

	case 0x03:
		printk(" TPSHP: 5/6,");
		break;

	case 0x04:
		printk(" TPSHP: 7/8,");
		break;

	default:
		printk(" TPSHP: Reserved,");

	}

	val = nxt6000_readreg(state, OFDM_TPS_RCVD_4);

	printk(" TPSMode: %s,", val & 0x01 ? "8K" : "2K");

	switch ((val >> 4) & 0x03) {

	case 0x00:
		printk(" TPSGuard: 1/32,");
		break;

	case 0x01:
		printk(" TPSGuard: 1/16,");
		break;

	case 0x02:
		printk(" TPSGuard: 1/8,");
		break;

	case 0x03:
		printk(" TPSGuard: 1/4,");
		break;

	}

	/* Strange magic required to gain access to RF_AGC_STATUS */
	nxt6000_readreg(state, RF_AGC_VAL_1);
	val = nxt6000_readreg(state, RF_AGC_STATUS);
	val = nxt6000_readreg(state, RF_AGC_STATUS);

	printk(" RF AGC LOCK: %d,", (val >> 4) & 0x01);
	printk("\n");
}