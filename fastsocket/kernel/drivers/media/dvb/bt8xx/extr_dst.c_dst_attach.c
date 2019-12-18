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
struct dvb_frontend_ops {int dummy; } ;
struct dvb_adapter {int dummy; } ;
struct TYPE_2__ {struct dst_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct dst_state {int dst_type; TYPE_1__ frontend; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_ERROR ; 
#define  DST_TYPE_IS_ATSC 131 
#define  DST_TYPE_IS_CABLE 130 
#define  DST_TYPE_IS_SAT 129 
#define  DST_TYPE_IS_TERR 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  dst_atsc_ops ; 
 int /*<<< orphan*/  dst_dvbc_ops ; 
 int /*<<< orphan*/  dst_dvbs_ops ; 
 int /*<<< orphan*/  dst_dvbt_ops ; 
 scalar_t__ dst_probe (struct dst_state*) ; 
 int /*<<< orphan*/  kfree (struct dst_state*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  verbose ; 

struct dst_state *dst_attach(struct dst_state *state, struct dvb_adapter *dvb_adapter)
{
	/* check if the ASIC is there */
	if (dst_probe(state) < 0) {
		kfree(state);
		return NULL;
	}
	/* determine settings based on type */
	/* create dvb_frontend */
	switch (state->dst_type) {
	case DST_TYPE_IS_TERR:
		memcpy(&state->frontend.ops, &dst_dvbt_ops, sizeof(struct dvb_frontend_ops));
		break;
	case DST_TYPE_IS_CABLE:
		memcpy(&state->frontend.ops, &dst_dvbc_ops, sizeof(struct dvb_frontend_ops));
		break;
	case DST_TYPE_IS_SAT:
		memcpy(&state->frontend.ops, &dst_dvbs_ops, sizeof(struct dvb_frontend_ops));
		break;
	case DST_TYPE_IS_ATSC:
		memcpy(&state->frontend.ops, &dst_atsc_ops, sizeof(struct dvb_frontend_ops));
		break;
	default:
		dprintk(verbose, DST_ERROR, 1, "unknown DST type. please report to the LinuxTV.org DVB mailinglist.");
		kfree(state);
		return NULL;
	}
	state->frontend.demodulator_priv = state;

	return state;				/*	Manu (DST is a card not a frontend)	*/
}