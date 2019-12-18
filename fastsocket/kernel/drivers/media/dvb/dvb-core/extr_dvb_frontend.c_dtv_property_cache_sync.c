#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_12__ {int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  constellation; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_11__ {int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_10__ {int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_14__ {TYPE_6__ vsb; TYPE_5__ ofdm; TYPE_4__ qam; TYPE_3__ qpsk; } ;
struct dvb_frontend_parameters {TYPE_7__ u; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct TYPE_8__ {int type; } ;
struct TYPE_9__ {TYPE_1__ info; } ;
struct dtv_frontend_properties {int bandwidth_hz; int /*<<< orphan*/  delivery_system; int /*<<< orphan*/  modulation; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  symbol_rate; int /*<<< orphan*/  rolloff; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend {TYPE_2__ ops; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDWIDTH_6_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_7_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
#define  FE_ATSC 131 
#define  FE_OFDM 130 
#define  FE_QAM 129 
#define  FE_QPSK 128 
 int /*<<< orphan*/  QPSK ; 
 int /*<<< orphan*/  ROLLOFF_35 ; 
 int /*<<< orphan*/  SYS_ATSC ; 
 int /*<<< orphan*/  SYS_DVBC_ANNEX_AC ; 
 int /*<<< orphan*/  SYS_DVBC_ANNEX_B ; 
 int /*<<< orphan*/  SYS_DVBS ; 
 int /*<<< orphan*/  SYS_DVBT ; 
 int /*<<< orphan*/  VSB_16 ; 
 int /*<<< orphan*/  VSB_8 ; 

__attribute__((used)) static void dtv_property_cache_sync(struct dvb_frontend *fe,
				    struct dvb_frontend_parameters *p)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	c->frequency = p->frequency;
	c->inversion = p->inversion;

	switch (fe->ops.info.type) {
	case FE_QPSK:
		c->modulation = QPSK;   /* implied for DVB-S in legacy API */
		c->rolloff = ROLLOFF_35;/* implied for DVB-S */
		c->symbol_rate = p->u.qpsk.symbol_rate;
		c->fec_inner = p->u.qpsk.fec_inner;
		c->delivery_system = SYS_DVBS;
		break;
	case FE_QAM:
		c->symbol_rate = p->u.qam.symbol_rate;
		c->fec_inner = p->u.qam.fec_inner;
		c->modulation = p->u.qam.modulation;
		c->delivery_system = SYS_DVBC_ANNEX_AC;
		break;
	case FE_OFDM:
		if (p->u.ofdm.bandwidth == BANDWIDTH_6_MHZ)
			c->bandwidth_hz = 6000000;
		else if (p->u.ofdm.bandwidth == BANDWIDTH_7_MHZ)
			c->bandwidth_hz = 7000000;
		else if (p->u.ofdm.bandwidth == BANDWIDTH_8_MHZ)
			c->bandwidth_hz = 8000000;
		else
			/* Including BANDWIDTH_AUTO */
			c->bandwidth_hz = 0;
		c->code_rate_HP = p->u.ofdm.code_rate_HP;
		c->code_rate_LP = p->u.ofdm.code_rate_LP;
		c->modulation = p->u.ofdm.constellation;
		c->transmission_mode = p->u.ofdm.transmission_mode;
		c->guard_interval = p->u.ofdm.guard_interval;
		c->hierarchy = p->u.ofdm.hierarchy_information;
		c->delivery_system = SYS_DVBT;
		break;
	case FE_ATSC:
		c->modulation = p->u.vsb.modulation;
		if ((c->modulation == VSB_8) || (c->modulation == VSB_16))
			c->delivery_system = SYS_ATSC;
		else
			c->delivery_system = SYS_DVBC_ANNEX_B;
		break;
	}
}