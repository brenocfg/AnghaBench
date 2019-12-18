#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_5__ {int transmission_mode; int guard_interval; int constellation; int hierarchy_information; int code_rate_HP; int code_rate_LP; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_6__ {TYPE_2__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_3__ u; } ;
struct TYPE_4__ {int diversity_delay; } ;
struct dib7000p_state {int div_sync_wait; int div_force_off; int /*<<< orphan*/  div_state; int /*<<< orphan*/  demod; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
#define  FEC_1_2 145 
#define  FEC_2_3 144 
#define  FEC_3_4 143 
#define  FEC_5_6 142 
#define  FEC_7_8 141 
#define  GUARD_INTERVAL_1_16 140 
#define  GUARD_INTERVAL_1_32 139 
#define  GUARD_INTERVAL_1_4 138 
#define  GUARD_INTERVAL_1_8 137 
#define  HIERARCHY_1 136 
#define  HIERARCHY_2 135 
#define  HIERARCHY_4 134 
#define  QAM_16 133 
#define  QAM_64 132 
#define  QPSK 131 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int /*<<< orphan*/  dib7000p_set_bandwidth (struct dib7000p_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_set_diversity_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 

__attribute__((used)) static void dib7000p_set_channel(struct dib7000p_state *state, struct dvb_frontend_parameters *ch, u8 seq)
{
	u16 value, est[4];

    dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->u.ofdm.bandwidth));

	/* nfft, guard, qam, alpha */
	value = 0;
	switch (ch->u.ofdm.transmission_mode) {
		case TRANSMISSION_MODE_2K: value |= (0 << 7); break;
		case TRANSMISSION_MODE_4K: value |= (2 << 7); break;
		default:
		case TRANSMISSION_MODE_8K: value |= (1 << 7); break;
	}
	switch (ch->u.ofdm.guard_interval) {
		case GUARD_INTERVAL_1_32: value |= (0 << 5); break;
		case GUARD_INTERVAL_1_16: value |= (1 << 5); break;
		case GUARD_INTERVAL_1_4:  value |= (3 << 5); break;
		default:
		case GUARD_INTERVAL_1_8:  value |= (2 << 5); break;
	}
	switch (ch->u.ofdm.constellation) {
		case QPSK:  value |= (0 << 3); break;
		case QAM_16: value |= (1 << 3); break;
		default:
		case QAM_64: value |= (2 << 3); break;
	}
	switch (HIERARCHY_1) {
		case HIERARCHY_2: value |= 2; break;
		case HIERARCHY_4: value |= 4; break;
		default:
		case HIERARCHY_1: value |= 1; break;
	}
	dib7000p_write_word(state, 0, value);
	dib7000p_write_word(state, 5, (seq << 4) | 1); /* do not force tps, search list 0 */

	/* P_dintl_native, P_dintlv_inv, P_hrch, P_code_rate, P_select_hp */
	value = 0;
	if (1 != 0)
		value |= (1 << 6);
	if (ch->u.ofdm.hierarchy_information == 1)
		value |= (1 << 4);
	if (1 == 1)
		value |= 1;
	switch ((ch->u.ofdm.hierarchy_information == 0 || 1 == 1) ? ch->u.ofdm.code_rate_HP : ch->u.ofdm.code_rate_LP) {
		case FEC_2_3: value |= (2 << 1); break;
		case FEC_3_4: value |= (3 << 1); break;
		case FEC_5_6: value |= (5 << 1); break;
		case FEC_7_8: value |= (7 << 1); break;
		default:
		case FEC_1_2: value |= (1 << 1); break;
	}
	dib7000p_write_word(state, 208, value);

	/* offset loop parameters */
	dib7000p_write_word(state, 26, 0x6680); // timf(6xxx)
	dib7000p_write_word(state, 32, 0x0003); // pha_off_max(xxx3)
	dib7000p_write_word(state, 29, 0x1273); // isi
	dib7000p_write_word(state, 33, 0x0005); // sfreq(xxx5)

	/* P_dvsy_sync_wait */
	switch (ch->u.ofdm.transmission_mode) {
		case TRANSMISSION_MODE_8K: value = 256; break;
		case TRANSMISSION_MODE_4K: value = 128; break;
		case TRANSMISSION_MODE_2K:
		default: value = 64; break;
	}
	switch (ch->u.ofdm.guard_interval) {
		case GUARD_INTERVAL_1_16: value *= 2; break;
		case GUARD_INTERVAL_1_8:  value *= 4; break;
		case GUARD_INTERVAL_1_4:  value *= 8; break;
		default:
		case GUARD_INTERVAL_1_32: value *= 1; break;
	}
	if (state->cfg.diversity_delay == 0)
		state->div_sync_wait = (value * 3) / 2 + 48; // add 50% SFN margin + compensate for one DVSY-fifo
	else
		state->div_sync_wait = (value * 3) / 2 + state->cfg.diversity_delay; // add 50% SFN margin + compensate for one DVSY-fifo

	/* deactive the possibility of diversity reception if extended interleaver */
	state->div_force_off = !1 && ch->u.ofdm.transmission_mode != TRANSMISSION_MODE_8K;
	dib7000p_set_diversity_in(&state->demod, state->div_state);

	/* channel estimation fine configuration */
	switch (ch->u.ofdm.constellation) {
		case QAM_64:
			est[0] = 0x0148;       /* P_adp_regul_cnt 0.04 */
			est[1] = 0xfff0;       /* P_adp_noise_cnt -0.002 */
			est[2] = 0x00a4;       /* P_adp_regul_ext 0.02 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.001 */
			break;
		case QAM_16:
			est[0] = 0x023d;       /* P_adp_regul_cnt 0.07 */
			est[1] = 0xffdf;       /* P_adp_noise_cnt -0.004 */
			est[2] = 0x00a4;       /* P_adp_regul_ext 0.02 */
			est[3] = 0xfff0;       /* P_adp_noise_ext -0.002 */
			break;
		default:
			est[0] = 0x099a;       /* P_adp_regul_cnt 0.3 */
			est[1] = 0xffae;       /* P_adp_noise_cnt -0.01 */
			est[2] = 0x0333;       /* P_adp_regul_ext 0.1 */
			est[3] = 0xfff8;       /* P_adp_noise_ext -0.002 */
			break;
	}
	for (value = 0; value < 4; value++)
		dib7000p_write_word(state, 187 + value, est[value]);
}