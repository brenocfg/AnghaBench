#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct TYPE_10__ {TYPE_4__* pll; } ;
struct TYPE_7__ {scalar_t__ transmission_mode; scalar_t__ guard_interval; scalar_t__ isdbt_sb_mode; TYPE_1__* layer; scalar_t__ inversion; } ;
struct TYPE_8__ {TYPE_2__ dtv_property_cache; } ;
struct dib8000_state {TYPE_5__ cfg; TYPE_3__ fe; } ;
struct TYPE_9__ {int internal; } ;
struct TYPE_6__ {int segment_count; scalar_t__ interleaving; int /*<<< orphan*/  fec; int /*<<< orphan*/  modulation; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_2_3 ; 
 void* GUARD_INTERVAL_1_8 ; 
 scalar_t__ GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  QAM_64 ; 
 void* TRANSMISSION_MODE_8K ; 
 scalar_t__ TRANSMISSION_MODE_AUTO ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_set_channel (struct dib8000_state*,unsigned char,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int dib8000_autosearch_start(struct dvb_frontend *fe)
{
	u8 factor;
	u32 value;
	struct dib8000_state *state = fe->demodulator_priv;

	int slist = 0;

	state->fe.dtv_property_cache.inversion = 0;
	if (!state->fe.dtv_property_cache.isdbt_sb_mode)
		state->fe.dtv_property_cache.layer[0].segment_count = 13;
	state->fe.dtv_property_cache.layer[0].modulation = QAM_64;
	state->fe.dtv_property_cache.layer[0].fec = FEC_2_3;
	state->fe.dtv_property_cache.layer[0].interleaving = 0;

	//choose the right list, in sb, always do everything
	if (state->fe.dtv_property_cache.isdbt_sb_mode) {
		state->fe.dtv_property_cache.transmission_mode = TRANSMISSION_MODE_8K;
		state->fe.dtv_property_cache.guard_interval = GUARD_INTERVAL_1_8;
		slist = 7;
		dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));
	} else {
		if (state->fe.dtv_property_cache.guard_interval == GUARD_INTERVAL_AUTO) {
			if (state->fe.dtv_property_cache.transmission_mode == TRANSMISSION_MODE_AUTO) {
				slist = 7;
				dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));	// P_mode = 1 to have autosearch start ok with mode2
			} else
				slist = 3;
		} else {
			if (state->fe.dtv_property_cache.transmission_mode == TRANSMISSION_MODE_AUTO) {
				slist = 2;
				dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));	// P_mode = 1
			} else
				slist = 0;
		}

		if (state->fe.dtv_property_cache.transmission_mode == TRANSMISSION_MODE_AUTO)
			state->fe.dtv_property_cache.transmission_mode = TRANSMISSION_MODE_8K;
		if (state->fe.dtv_property_cache.guard_interval == GUARD_INTERVAL_AUTO)
			state->fe.dtv_property_cache.guard_interval = GUARD_INTERVAL_1_8;

		dprintk("using list for autosearch : %d", slist);
		dib8000_set_channel(state, (unsigned char)slist, 1);
		//dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));  // P_mode = 1

		factor = 1;

		//set lock_mask values
		dib8000_write_word(state, 6, 0x4);
		dib8000_write_word(state, 7, 0x8);
		dib8000_write_word(state, 8, 0x1000);

		//set lock_mask wait time values
		value = 50 * state->cfg.pll->internal * factor;
		dib8000_write_word(state, 11, (u16) ((value >> 16) & 0xffff));	// lock0 wait time
		dib8000_write_word(state, 12, (u16) (value & 0xffff));	// lock0 wait time
		value = 100 * state->cfg.pll->internal * factor;
		dib8000_write_word(state, 13, (u16) ((value >> 16) & 0xffff));	// lock1 wait time
		dib8000_write_word(state, 14, (u16) (value & 0xffff));	// lock1 wait time
		value = 1000 * state->cfg.pll->internal * factor;
		dib8000_write_word(state, 15, (u16) ((value >> 16) & 0xffff));	// lock2 wait time
		dib8000_write_word(state, 16, (u16) (value & 0xffff));	// lock2 wait time

		value = dib8000_read_word(state, 0);
		dib8000_write_word(state, 0, (u16) ((1 << 15) | value));
		dib8000_read_word(state, 1284);	// reset the INT. n_irq_pending
		dib8000_write_word(state, 0, (u16) value);

	}

	return 0;
}