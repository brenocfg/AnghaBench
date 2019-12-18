#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dvb_frontend_parameters {int dummy; } ;
struct TYPE_4__ {int bandwidth_hz; int isdbt_sb_mode; int inversion; int isdbt_partial_reception; TYPE_1__* layer; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; } ;
struct dvb_frontend {TYPE_2__ dtv_property_cache; struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int dummy; } ;
struct TYPE_3__ {int segment_count; int interleaving; int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQPSK ; 
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_2_3 ; 
 int /*<<< orphan*/  FEC_3_4 ; 
 int /*<<< orphan*/  FEC_5_6 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_16 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_4 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_8 ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_8K ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 

__attribute__((used)) static int dib8000_get_frontend(struct dvb_frontend *fe, struct dvb_frontend_parameters *fep)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 i, val = 0;

	fe->dtv_property_cache.bandwidth_hz = 6000000;

	fe->dtv_property_cache.isdbt_sb_mode = dib8000_read_word(state, 508) & 0x1;

	val = dib8000_read_word(state, 570);
	fe->dtv_property_cache.inversion = (val & 0x40) >> 6;
	switch ((val & 0x30) >> 4) {
	case 1:
		fe->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_2K;
		break;
	case 3:
	default:
		fe->dtv_property_cache.transmission_mode = TRANSMISSION_MODE_8K;
		break;
	}

	switch (val & 0x3) {
	case 0:
		fe->dtv_property_cache.guard_interval = GUARD_INTERVAL_1_32;
		dprintk("dib8000_get_frontend GI = 1/32 ");
		break;
	case 1:
		fe->dtv_property_cache.guard_interval = GUARD_INTERVAL_1_16;
		dprintk("dib8000_get_frontend GI = 1/16 ");
		break;
	case 2:
		dprintk("dib8000_get_frontend GI = 1/8 ");
		fe->dtv_property_cache.guard_interval = GUARD_INTERVAL_1_8;
		break;
	case 3:
		dprintk("dib8000_get_frontend GI = 1/4 ");
		fe->dtv_property_cache.guard_interval = GUARD_INTERVAL_1_4;
		break;
	}

	val = dib8000_read_word(state, 505);
	fe->dtv_property_cache.isdbt_partial_reception = val & 1;
	dprintk("dib8000_get_frontend : partial_reception = %d ", fe->dtv_property_cache.isdbt_partial_reception);

	for (i = 0; i < 3; i++) {
		val = dib8000_read_word(state, 493 + i);
		fe->dtv_property_cache.layer[i].segment_count = val & 0x0F;
		dprintk("dib8000_get_frontend : Layer %d segments = %d ", i, fe->dtv_property_cache.layer[i].segment_count);

		val = dib8000_read_word(state, 499 + i);
		fe->dtv_property_cache.layer[i].interleaving = val & 0x3;
		dprintk("dib8000_get_frontend : Layer %d time_intlv = %d ", i, fe->dtv_property_cache.layer[i].interleaving);

		val = dib8000_read_word(state, 481 + i);
		switch (val & 0x7) {
		case 1:
			fe->dtv_property_cache.layer[i].fec = FEC_1_2;
			dprintk("dib8000_get_frontend : Layer %d Code Rate = 1/2 ", i);
			break;
		case 2:
			fe->dtv_property_cache.layer[i].fec = FEC_2_3;
			dprintk("dib8000_get_frontend : Layer %d Code Rate = 2/3 ", i);
			break;
		case 3:
			fe->dtv_property_cache.layer[i].fec = FEC_3_4;
			dprintk("dib8000_get_frontend : Layer %d Code Rate = 3/4 ", i);
			break;
		case 5:
			fe->dtv_property_cache.layer[i].fec = FEC_5_6;
			dprintk("dib8000_get_frontend : Layer %d Code Rate = 5/6 ", i);
			break;
		default:
			fe->dtv_property_cache.layer[i].fec = FEC_7_8;
			dprintk("dib8000_get_frontend : Layer %d Code Rate = 7/8 ", i);
			break;
		}

		val = dib8000_read_word(state, 487 + i);
		switch (val & 0x3) {
		case 0:
			dprintk("dib8000_get_frontend : Layer %d DQPSK ", i);
			fe->dtv_property_cache.layer[i].modulation = DQPSK;
			break;
		case 1:
			fe->dtv_property_cache.layer[i].modulation = QPSK;
			dprintk("dib8000_get_frontend : Layer %d QPSK ", i);
			break;
		case 2:
			fe->dtv_property_cache.layer[i].modulation = QAM_16;
			dprintk("dib8000_get_frontend : Layer %d QAM16 ", i);
			break;
		case 3:
		default:
			dprintk("dib8000_get_frontend : Layer %d QAM64 ", i);
			fe->dtv_property_cache.layer[i].modulation = QAM_64;
			break;
		}
	}
	return 0;
}