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
typedef  int u8 ;
struct ttusbdecfe_state {TYPE_1__* config; } ;
struct dvb_frontend {scalar_t__ demodulator_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; int /*<<< orphan*/  msg; } ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_command ) (struct dvb_frontend*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttusbdecfe_dvbs_diseqc_send_master_cmd(struct dvb_frontend* fe, struct dvb_diseqc_master_cmd *cmd)
{
	struct ttusbdecfe_state* state = (struct ttusbdecfe_state*) fe->demodulator_priv;
	u8 b[] = { 0x00, 0xff, 0x00, 0x00,
		   0x00, 0x00, 0x00, 0x00,
		   0x00, 0x00 };

	memcpy(&b[4], cmd->msg, cmd->msg_len);

	state->config->send_command(fe, 0x72,
				    sizeof(b) - (6 - cmd->msg_len), b,
				    NULL, NULL);

	return 0;
}