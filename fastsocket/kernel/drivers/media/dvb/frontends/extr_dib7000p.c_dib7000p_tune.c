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
typedef  int u16 ;
struct TYPE_5__ {int transmission_mode; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_6__ {TYPE_2__ ofdm; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; } ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct TYPE_4__ {scalar_t__ spur_protect; } ;
struct dib7000p_state {scalar_t__ timf; TYPE_1__ cfg; scalar_t__ sfn_workaround_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_TO_KHZ (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  TRANSMISSION_MODE_2K 130 
#define  TRANSMISSION_MODE_4K 129 
#define  TRANSMISSION_MODE_8K 128 
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_set_bandwidth (struct dib7000p_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_set_channel (struct dib7000p_state*,struct dvb_frontend_parameters*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_spur_protect (struct dib7000p_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib7000p_update_timf (struct dib7000p_state*) ; 
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib7000p_tune(struct dvb_frontend *demod, struct dvb_frontend_parameters *ch)
{
	struct dib7000p_state *state = demod->demodulator_priv;
	u16 tmp = 0;

	if (ch != NULL)
		dib7000p_set_channel(state, ch, 0);
	else
		return -EINVAL;

	// restart demod
	dib7000p_write_word(state, 770, 0x4000);
	dib7000p_write_word(state, 770, 0x0000);
	msleep(45);

	/* P_ctrl_inh_cor=0, P_ctrl_alpha_cor=4, P_ctrl_inh_isi=0, P_ctrl_alpha_isi=3, P_ctrl_inh_cor4=1, P_ctrl_alpha_cor4=3 */
	tmp = (0 << 14) | (4 << 10) | (0 << 9) | (3 << 5) | (1 << 4) | (0x3);
	if (state->sfn_workaround_active) {
		dprintk( "SFN workaround is active");
		tmp |= (1 << 9);
		dib7000p_write_word(state, 166, 0x4000); // P_pha3_force_pha_shift
	} else {
		dib7000p_write_word(state, 166, 0x0000); // P_pha3_force_pha_shift
	}
	dib7000p_write_word(state, 29, tmp);

	// never achieved a lock with that bandwidth so far - wait for osc-freq to update
	if (state->timf == 0)
		msleep(200);

	/* offset loop parameters */

	/* P_timf_alpha, P_corm_alpha=6, P_corm_thres=0x80 */
	tmp = (6 << 8) | 0x80;
	switch (ch->u.ofdm.transmission_mode) {
		case TRANSMISSION_MODE_2K: tmp |= (7 << 12); break;
		case TRANSMISSION_MODE_4K: tmp |= (8 << 12); break;
		default:
		case TRANSMISSION_MODE_8K: tmp |= (9 << 12); break;
	}
	dib7000p_write_word(state, 26, tmp);  /* timf_a(6xxx) */

	/* P_ctrl_freeze_pha_shift=0, P_ctrl_pha_off_max */
	tmp = (0 << 4);
	switch (ch->u.ofdm.transmission_mode) {
		case TRANSMISSION_MODE_2K: tmp |= 0x6; break;
		case TRANSMISSION_MODE_4K: tmp |= 0x7; break;
		default:
		case TRANSMISSION_MODE_8K: tmp |= 0x8; break;
	}
	dib7000p_write_word(state, 32,  tmp);

	/* P_ctrl_sfreq_inh=0, P_ctrl_sfreq_step */
	tmp = (0 << 4);
	switch (ch->u.ofdm.transmission_mode) {
		case TRANSMISSION_MODE_2K: tmp |= 0x6; break;
		case TRANSMISSION_MODE_4K: tmp |= 0x7; break;
		default:
		case TRANSMISSION_MODE_8K: tmp |= 0x8; break;
	}
	dib7000p_write_word(state, 33,  tmp);

	tmp = dib7000p_read_word(state,509);
	if (!((tmp >> 6) & 0x1)) {
		/* restart the fec */
		tmp = dib7000p_read_word(state,771);
		dib7000p_write_word(state, 771, tmp | (1 << 1));
		dib7000p_write_word(state, 771, tmp);
		msleep(10);
		tmp = dib7000p_read_word(state,509);
	}

	// we achieved a lock - it's time to update the osc freq
	if ((tmp >> 6) & 0x1)
		dib7000p_update_timf(state);

	if (state->cfg.spur_protect)
		dib7000p_spur_protect(state, ch->frequency/1000, BANDWIDTH_TO_KHZ(ch->u.ofdm.bandwidth));

    dib7000p_set_bandwidth(state, BANDWIDTH_TO_KHZ(ch->u.ofdm.bandwidth));
	return 0;
}