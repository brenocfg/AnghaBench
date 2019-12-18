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
struct tda10023_state {int dummy; } ;
struct TYPE_7__ {int modulation; int /*<<< orphan*/  symbol_rate; } ;
struct TYPE_8__ {TYPE_3__ qam; } ;
struct dvb_frontend_parameters {TYPE_4__ u; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_params ) (struct dvb_frontend*,struct dvb_frontend_parameters*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct tda10023_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda10023_set_symbolrate (struct tda10023_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tda10023_setup_reg0 (struct tda10023_state*,int) ; 
 int /*<<< orphan*/  tda10023_writebit (struct tda10023_state*,int,int,int) ; 
 int /*<<< orphan*/  tda10023_writereg (struct tda10023_state*,int,int) ; 

__attribute__((used)) static int tda10023_set_parameters (struct dvb_frontend *fe,
			    struct dvb_frontend_parameters *p)
{
	struct tda10023_state* state = fe->demodulator_priv;

	static int qamvals[6][6] = {
		//  QAM   LOCKTHR  MSETH   AREF AGCREFNYQ  ERAGCNYQ_THD
		{ (5<<2),  0x78,    0x8c,   0x96,   0x78,   0x4c  },  // 4 QAM
		{ (0<<2),  0x87,    0xa2,   0x91,   0x8c,   0x57  },  // 16 QAM
		{ (1<<2),  0x64,    0x74,   0x96,   0x8c,   0x57  },  // 32 QAM
		{ (2<<2),  0x46,    0x43,   0x6a,   0x6a,   0x44  },  // 64 QAM
		{ (3<<2),  0x36,    0x34,   0x7e,   0x78,   0x4c  },  // 128 QAM
		{ (4<<2),  0x26,    0x23,   0x6c,   0x5c,   0x3c  },  // 256 QAM
	};

	int qam = p->u.qam.modulation;

	if (qam < 0 || qam > 5)
		return -EINVAL;

	if (fe->ops.tuner_ops.set_params) {
		fe->ops.tuner_ops.set_params(fe, p);
		if (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	}

	tda10023_set_symbolrate (state, p->u.qam.symbol_rate);
	tda10023_writereg (state, 0x05, qamvals[qam][1]);
	tda10023_writereg (state, 0x08, qamvals[qam][2]);
	tda10023_writereg (state, 0x09, qamvals[qam][3]);
	tda10023_writereg (state, 0xb4, qamvals[qam][4]);
	tda10023_writereg (state, 0xb6, qamvals[qam][5]);

//	tda10023_writereg (state, 0x04, (p->inversion?0x12:0x32));
//	tda10023_writebit (state, 0x04, 0x60, (p->inversion?0:0x20));
	tda10023_writebit (state, 0x04, 0x40, 0x40);
	tda10023_setup_reg0 (state, qamvals[qam][0]);

	return 0;
}