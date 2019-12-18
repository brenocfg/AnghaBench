#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct sp8870_state {int dummy; } ;
struct TYPE_7__ {scalar_t__ bandwidth; scalar_t__ transmission_mode; } ;
struct TYPE_8__ {TYPE_3__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct sp8870_state* demodulator_priv; } ;

/* Variables and functions */
 scalar_t__ BANDWIDTH_6_MHZ ; 
 scalar_t__ BANDWIDTH_7_MHZ ; 
 scalar_t__ TRANSMISSION_MODE_2K ; 
 int configure_reg0xc05 (struct dvb_frontend_parameters*,int*) ; 
 int /*<<< orphan*/  sp8870_microcontroller_start (struct sp8870_state*) ; 
 int /*<<< orphan*/  sp8870_microcontroller_stop (struct sp8870_state*) ; 
 int /*<<< orphan*/  sp8870_readreg (struct sp8870_state*,int) ; 
 int /*<<< orphan*/  sp8870_writereg (struct sp8870_state*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sp8870_set_frontend_parameters (struct dvb_frontend* fe,
					   struct dvb_frontend_parameters *p)
{
	struct sp8870_state* state = fe->demodulator_priv;
	int  err;
	u16 reg0xc05;

	if ((err = configure_reg0xc05(p, &reg0xc05)))
		return err;

	// system controller stop
	sp8870_microcontroller_stop(state);

	// set tuner parameters
	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe, p);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	// sample rate correction bit [23..17]
	sp8870_writereg(state, 0x0319, 0x000A);

	// sample rate correction bit [16..0]
	sp8870_writereg(state, 0x031A, 0x0AAB);

	// integer carrier offset
	sp8870_writereg(state, 0x0309, 0x0400);

	// fractional carrier offset
	sp8870_writereg(state, 0x030A, 0x0000);

	// filter for 6/7/8 Mhz channel
	if (p->u.ofdm.bandwidth == BANDWIDTH_6_MHZ)
		sp8870_writereg(state, 0x0311, 0x0002);
	else if (p->u.ofdm.bandwidth == BANDWIDTH_7_MHZ)
		sp8870_writereg(state, 0x0311, 0x0001);
	else
		sp8870_writereg(state, 0x0311, 0x0000);

	// scan order: 2k first = 0x0000, 8k first = 0x0001
	if (p->u.ofdm.transmission_mode == TRANSMISSION_MODE_2K)
		sp8870_writereg(state, 0x0338, 0x0000);
	else
		sp8870_writereg(state, 0x0338, 0x0001);

	sp8870_writereg(state, 0xc05, reg0xc05);

	// read status reg in order to clear pending irqs
	sp8870_readreg(state, 0x200);

	// system controller start
	sp8870_microcontroller_start(state);

	return 0;
}