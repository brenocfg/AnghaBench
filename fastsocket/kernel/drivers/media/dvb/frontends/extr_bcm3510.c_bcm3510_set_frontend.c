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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int modulation; } ;
struct TYPE_6__ {TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {int /*<<< orphan*/  frequency; TYPE_2__ u; } ;
struct dvb_frontend {struct bcm3510_state* demodulator_priv; } ;
struct TYPE_8__ {int MODE; int NTSCSWEEP; int FA; scalar_t__ BW; scalar_t__ OFFSET; } ;
struct TYPE_7__ {int SYM_RATE; int IF_FREQ; } ;
struct bcm3510_hab_cmd_ext_acquire {TYPE_4__ ACQUIRE0; TYPE_3__ ACQUIRE1; } ;
struct bcm3510_state {int status_check_interval; struct bcm3510_hab_cmd_ext_acquire status2; struct bcm3510_hab_cmd_ext_acquire status1; } ;
struct bcm3510_hab_cmd_bert_control {scalar_t__ unused; scalar_t__ BE; } ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  bert ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACQUIRE ; 
 int /*<<< orphan*/  CMD_STATE_CONTROL ; 
 int EINVAL ; 
 int /*<<< orphan*/  MSGID_BERT_CONTROL ; 
 int /*<<< orphan*/  MSGID_BERT_SET ; 
 int /*<<< orphan*/  MSGID_EXT_TUNER_ACQUIRE ; 
#define  QAM_256 131 
#define  QAM_64 130 
#define  VSB_16 129 
#define  VSB_8 128 
 int /*<<< orphan*/  bcm3510_bert_reset (struct bcm3510_state*) ; 
 int /*<<< orphan*/  bcm3510_do_hab_cmd (struct bcm3510_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bcm3510_set_freq (struct bcm3510_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bcm3510_hab_cmd_ext_acquire*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int bcm3510_set_frontend(struct dvb_frontend* fe,
					     struct dvb_frontend_parameters *p)
{
	struct bcm3510_state* st = fe->demodulator_priv;
	struct bcm3510_hab_cmd_ext_acquire cmd;
	struct bcm3510_hab_cmd_bert_control bert;
	int ret;

	memset(&cmd,0,sizeof(cmd));
	switch (p->u.vsb.modulation) {
		case QAM_256:
			cmd.ACQUIRE0.MODE = 0x1;
			cmd.ACQUIRE1.SYM_RATE = 0x1;
			cmd.ACQUIRE1.IF_FREQ = 0x1;
			break;
		case QAM_64:
			cmd.ACQUIRE0.MODE = 0x2;
			cmd.ACQUIRE1.SYM_RATE = 0x2;
			cmd.ACQUIRE1.IF_FREQ = 0x1;
			break;
/*		case QAM_256:
			cmd.ACQUIRE0.MODE = 0x3;
			break;
		case QAM_128:
			cmd.ACQUIRE0.MODE = 0x4;
			break;
		case QAM_64:
			cmd.ACQUIRE0.MODE = 0x5;
			break;
		case QAM_32:
			cmd.ACQUIRE0.MODE = 0x6;
			break;
		case QAM_16:
			cmd.ACQUIRE0.MODE = 0x7;
			break;*/
		case VSB_8:
			cmd.ACQUIRE0.MODE = 0x8;
			cmd.ACQUIRE1.SYM_RATE = 0x0;
			cmd.ACQUIRE1.IF_FREQ = 0x0;
			break;
		case VSB_16:
			cmd.ACQUIRE0.MODE = 0x9;
			cmd.ACQUIRE1.SYM_RATE = 0x0;
			cmd.ACQUIRE1.IF_FREQ = 0x0;
		default:
			return -EINVAL;
	};
	cmd.ACQUIRE0.OFFSET = 0;
	cmd.ACQUIRE0.NTSCSWEEP = 1;
	cmd.ACQUIRE0.FA = 1;
	cmd.ACQUIRE0.BW = 0;

/*	if (enableOffset) {
		cmd.IF_OFFSET0 = xx;
		cmd.IF_OFFSET1 = xx;

		cmd.SYM_OFFSET0 = xx;
		cmd.SYM_OFFSET1 = xx;
		if (enableNtscSweep) {
			cmd.NTSC_OFFSET0;
			cmd.NTSC_OFFSET1;
		}
	} */
	bcm3510_do_hab_cmd(st, CMD_ACQUIRE, MSGID_EXT_TUNER_ACQUIRE, (u8 *) &cmd, sizeof(cmd), NULL, 0);

/* doing it with different MSGIDs, data book and source differs */
	bert.BE = 0;
	bert.unused = 0;
	bcm3510_do_hab_cmd(st, CMD_STATE_CONTROL, MSGID_BERT_CONTROL, (u8 *) &bert, sizeof(bert), NULL, 0);
	bcm3510_do_hab_cmd(st, CMD_STATE_CONTROL, MSGID_BERT_SET, (u8 *) &bert, sizeof(bert), NULL, 0);

	bcm3510_bert_reset(st);

	if ((ret = bcm3510_set_freq(st,p->frequency)) < 0)
		return ret;

	memset(&st->status1,0,sizeof(st->status1));
	memset(&st->status2,0,sizeof(st->status2));
	st->status_check_interval = 500;

/* Give the AP some time */
	msleep(200);

	return 0;
}