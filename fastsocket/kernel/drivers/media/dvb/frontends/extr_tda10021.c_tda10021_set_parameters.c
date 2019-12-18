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
typedef  int u8 ;
struct tda10021_state {int const pwm; } ;
struct TYPE_7__ {int modulation; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_8__ {TYPE_3__ qam; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  inversion; TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct tda10021_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  _tda10021_writereg (struct tda10021_state*,int,int const) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda10021_set_symbolrate (struct tda10021_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda10021_setup_reg0 (struct tda10021_state*,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda10021_set_parameters (struct dvb_frontend *fe,
			    struct dvb_frontend_parameters *p)
{
	struct tda10021_state* state = fe->demodulator_priv;

	//table for QAM4-QAM256 ready  QAM4  QAM16 QAM32 QAM64 QAM128 QAM256
	//CONF
	static const u8 reg0x00 [] = { 0x14, 0x00, 0x04, 0x08, 0x0c,  0x10 };
	//AGCREF value
	static const u8 reg0x01 [] = { 0x78, 0x8c, 0x8c, 0x6a, 0x78,  0x5c };
	//LTHR value
	static const u8 reg0x05 [] = { 0x78, 0x87, 0x64, 0x46, 0x36,  0x26 };
	//MSETH
	static const u8 reg0x08 [] = { 0x8c, 0xa2, 0x74, 0x43, 0x34,  0x23 };
	//AREF
	static const u8 reg0x09 [] = { 0x96, 0x91, 0x96, 0x6a, 0x7e,  0x6b };

	int qam = p->u.qam.modulation;

	if (qam < 0 || qam > 5)
		return -EINVAL;

	if (p->inversion != INVERSION_ON && p->inversion != INVERSION_OFF)
		return -EINVAL;

	//printk("tda10021: set frequency to %d qam=%d symrate=%d\n", p->frequency,qam,p->u.qam.symbol_rate);

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe, p);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	tda10021_set_symbolrate (state, p->u.qam.symbol_rate);
	_tda10021_writereg (state, 0x34, state->pwm);

	_tda10021_writereg (state, 0x01, reg0x01[qam]);
	_tda10021_writereg (state, 0x05, reg0x05[qam]);
	_tda10021_writereg (state, 0x08, reg0x08[qam]);
	_tda10021_writereg (state, 0x09, reg0x09[qam]);

	tda10021_setup_reg0 (state, reg0x00[qam], p->inversion);

	return 0;
}