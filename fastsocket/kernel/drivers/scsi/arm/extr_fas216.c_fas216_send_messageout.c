#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct message {int length; unsigned int fifo; int /*<<< orphan*/ * msg; } ;
struct TYPE_8__ {int /*<<< orphan*/  phase; int /*<<< orphan*/  msgs; } ;
struct TYPE_9__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 unsigned int CFIS_CF ; 
 int /*<<< orphan*/  CMD_FLUSHFIFO ; 
 int /*<<< orphan*/  CMD_TRANSFERINFO ; 
 int /*<<< orphan*/  NOP ; 
 int /*<<< orphan*/  PHASE_MSGOUT ; 
 int /*<<< orphan*/  REG_CFIS ; 
 int /*<<< orphan*/  REG_FF ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_2__*) ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_2__*,int /*<<< orphan*/ ) ; 
 unsigned int fas216_readb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fas216_writeb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct message* msgqueue_getmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int msgqueue_msglength (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fas216_send_messageout(FAS216_Info *info, int start)
{
	unsigned int tot_msglen = msgqueue_msglength(&info->scsi.msgs);

	fas216_checkmagic(info);

	fas216_cmd(info, CMD_FLUSHFIFO);

	if (tot_msglen) {
		struct message *msg;
		int msgnr = 0;

		while ((msg = msgqueue_getmsg(&info->scsi.msgs, msgnr++)) != NULL) {
			int i;

			for (i = start; i < msg->length; i++)
				fas216_writeb(info, REG_FF, msg->msg[i]);

			msg->fifo = tot_msglen - (fas216_readb(info, REG_CFIS) & CFIS_CF);
			start = 0;
		}
	} else
		fas216_writeb(info, REG_FF, NOP);

	fas216_cmd(info, CMD_TRANSFERINFO);

	info->scsi.phase = PHASE_MSGOUT;
}