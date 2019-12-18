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
struct firedtv {scalar_t__ avc_data; } ;
struct TYPE_5__ {scalar_t__ fec_inner; int modulation; } ;
struct TYPE_4__ {int symbol_rate; int fec_inner; } ;
struct TYPE_6__ {TYPE_2__ qam; TYPE_1__ qpsk; } ;
struct dvb_frontend_parameters {int frequency; TYPE_3__ u; } ;
struct avc_command_frame {int* operand; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_OPCODE_DSD ; 
#define  FEC_1_2 141 
#define  FEC_2_3 140 
#define  FEC_3_4 139 
#define  FEC_4_5 138 
#define  FEC_5_6 137 
#define  FEC_7_8 136 
#define  FEC_8_9 135 
#define  FEC_AUTO 134 
#define  QAM_128 133 
#define  QAM_16 132 
#define  QAM_256 131 
#define  QAM_32 130 
#define  QAM_64 129 
#define  QAM_AUTO 128 
 int add_pid_filter (struct firedtv*,int*) ; 

__attribute__((used)) static int avc_tuner_dsd_dvb_c(struct firedtv *fdtv,
			       struct dvb_frontend_parameters *params)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;

	c->opcode = AVC_OPCODE_DSD;

	c->operand[0] = 0;    /* source plug */
	c->operand[1] = 0xd2; /* subfunction replace */
	c->operand[2] = 0x20; /* system id = DVB */
	c->operand[3] = 0x00; /* antenna number */
	c->operand[4] = 0x11; /* system_specific_multiplex selection_length */

	/* multiplex_valid_flags, high byte */
	c->operand[5] =   0 << 7 /* reserved */
			| 0 << 6 /* Polarisation */
			| 0 << 5 /* Orbital_Pos */
			| 1 << 4 /* Frequency */
			| 1 << 3 /* Symbol_Rate */
			| 0 << 2 /* FEC_outer */
			| (params->u.qam.fec_inner  != FEC_AUTO ? 1 << 1 : 0)
			| (params->u.qam.modulation != QAM_AUTO ? 1 << 0 : 0);

	/* multiplex_valid_flags, low byte */
	c->operand[6] =   0 << 7 /* NetworkID */
			| 0 << 0 /* reserved */ ;

	c->operand[7]  = 0x00;
	c->operand[8]  = 0x00;
	c->operand[9]  = 0x00;
	c->operand[10] = 0x00;

	c->operand[11] = (((params->frequency / 4000) >> 16) & 0xff) | (2 << 6);
	c->operand[12] = ((params->frequency / 4000) >> 8) & 0xff;
	c->operand[13] = (params->frequency / 4000) & 0xff;
	c->operand[14] = ((params->u.qpsk.symbol_rate / 1000) >> 12) & 0xff;
	c->operand[15] = ((params->u.qpsk.symbol_rate / 1000) >> 4) & 0xff;
	c->operand[16] = ((params->u.qpsk.symbol_rate / 1000) << 4) & 0xf0;
	c->operand[17] = 0x00;

	switch (params->u.qpsk.fec_inner) {
	case FEC_1_2:	c->operand[18] = 0x1; break;
	case FEC_2_3:	c->operand[18] = 0x2; break;
	case FEC_3_4:	c->operand[18] = 0x3; break;
	case FEC_5_6:	c->operand[18] = 0x4; break;
	case FEC_7_8:	c->operand[18] = 0x5; break;
	case FEC_8_9:	c->operand[18] = 0x6; break;
	case FEC_4_5:	c->operand[18] = 0x8; break;
	case FEC_AUTO:
	default:	c->operand[18] = 0x0;
	}

	switch (params->u.qam.modulation) {
	case QAM_16:	c->operand[19] = 0x08; break;
	case QAM_32:	c->operand[19] = 0x10; break;
	case QAM_64:	c->operand[19] = 0x18; break;
	case QAM_128:	c->operand[19] = 0x20; break;
	case QAM_256:	c->operand[19] = 0x28; break;
	case QAM_AUTO:
	default:	c->operand[19] = 0x00;
	}

	c->operand[20] = 0x00;
	c->operand[21] = 0x00;

	return 22 + add_pid_filter(fdtv, &c->operand[22]);
}