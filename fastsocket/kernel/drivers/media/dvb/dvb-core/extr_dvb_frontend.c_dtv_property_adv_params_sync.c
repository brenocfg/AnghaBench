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
struct TYPE_5__ {int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  constellation; } ;
struct TYPE_4__ {int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_6__ {TYPE_2__ ofdm; TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {TYPE_3__ u; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend_private {struct dvb_frontend_parameters parameters; } ;
struct dtv_frontend_properties {int modulation; scalar_t__ delivery_system; int bandwidth_hz; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  symbol_rate; } ;
struct dvb_frontend {struct dvb_frontend_private* frontend_priv; struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
#define  APSK_16 131 
#define  APSK_32 130 
 int /*<<< orphan*/  BANDWIDTH_6_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_7_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_8_MHZ ; 
 int /*<<< orphan*/  BANDWIDTH_AUTO ; 
 void* FEC_AUTO ; 
 int /*<<< orphan*/  GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  HIERARCHY_AUTO ; 
#define  PSK_8 129 
 int /*<<< orphan*/  QAM_AUTO ; 
#define  QPSK 128 
 scalar_t__ SYS_ISDBT ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_AUTO ; 

__attribute__((used)) static void dtv_property_adv_params_sync(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct dvb_frontend_private *fepriv = fe->frontend_priv;
	struct dvb_frontend_parameters *p = &fepriv->parameters;

	p->frequency = c->frequency;
	p->inversion = c->inversion;

	switch(c->modulation) {
	case PSK_8:
	case APSK_16:
	case APSK_32:
	case QPSK:
		p->u.qpsk.symbol_rate = c->symbol_rate;
		p->u.qpsk.fec_inner = c->fec_inner;
		break;
	default:
		break;
	}

	if(c->delivery_system == SYS_ISDBT) {
		/* Fake out a generic DVB-T request so we pass validation in the ioctl */
		p->frequency = c->frequency;
		p->inversion = c->inversion;
		p->u.ofdm.constellation = QAM_AUTO;
		p->u.ofdm.code_rate_HP = FEC_AUTO;
		p->u.ofdm.code_rate_LP = FEC_AUTO;
		p->u.ofdm.transmission_mode = TRANSMISSION_MODE_AUTO;
		p->u.ofdm.guard_interval = GUARD_INTERVAL_AUTO;
		p->u.ofdm.hierarchy_information = HIERARCHY_AUTO;
		if (c->bandwidth_hz == 8000000)
			p->u.ofdm.bandwidth = BANDWIDTH_8_MHZ;
		else if (c->bandwidth_hz == 7000000)
			p->u.ofdm.bandwidth = BANDWIDTH_7_MHZ;
		else if (c->bandwidth_hz == 6000000)
			p->u.ofdm.bandwidth = BANDWIDTH_6_MHZ;
		else
			p->u.ofdm.bandwidth = BANDWIDTH_AUTO;
	}
}