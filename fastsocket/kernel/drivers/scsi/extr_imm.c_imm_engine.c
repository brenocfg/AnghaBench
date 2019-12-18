#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int phase; int this_residual; int /*<<< orphan*/  buffers_residual; int /*<<< orphan*/ * ptr; TYPE_3__* buffer; } ;
struct scsi_cmnd {int result; TYPE_1__ SCp; } ;
struct TYPE_13__ {unsigned short base; int rd; int dp; int /*<<< orphan*/  mode; scalar_t__ jstart; scalar_t__ failed; } ;
typedef  TYPE_2__ imm_struct ;
struct TYPE_14__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_EPP_MAYBE ; 
 int /*<<< orphan*/  DID_BUS_BUSY ; 
 int /*<<< orphan*/  DID_ERROR ; 
 int /*<<< orphan*/  DID_NO_CONNECT ; 
 int DID_OK ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IMM_NIBBLE ; 
 int /*<<< orphan*/  IMM_PS2 ; 
 unsigned char STATUS_MASK ; 
 int imm_completion (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  imm_connect (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_fail (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_in (TYPE_2__*,unsigned char*,int) ; 
 int /*<<< orphan*/  imm_negotiate (TYPE_2__*) ; 
 int /*<<< orphan*/  imm_select (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_send_command (struct scsi_cmnd*) ; 
 unsigned char imm_wait (TYPE_2__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  printk (char*) ; 
 int r_str (unsigned short) ; 
 int /*<<< orphan*/  scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sg_count (struct scsi_cmnd*) ; 
 TYPE_3__* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_3__*) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  w_ctr (unsigned short,int) ; 

__attribute__((used)) static int imm_engine(imm_struct *dev, struct scsi_cmnd *cmd)
{
	unsigned short ppb = dev->base;
	unsigned char l = 0, h = 0;
	int retv, x;

	/* First check for any errors that may have occurred
	 * Here we check for internal errors
	 */
	if (dev->failed)
		return 0;

	switch (cmd->SCp.phase) {
	case 0:		/* Phase 0 - Waiting for parport */
		if (time_after(jiffies, dev->jstart + HZ)) {
			/*
			 * We waited more than a second
			 * for parport to call us
			 */
			imm_fail(dev, DID_BUS_BUSY);
			return 0;
		}
		return 1;	/* wait until imm_wakeup claims parport */
		/* Phase 1 - Connected */
	case 1:
		imm_connect(dev, CONNECT_EPP_MAYBE);
		cmd->SCp.phase++;

		/* Phase 2 - We are now talking to the scsi bus */
	case 2:
		if (!imm_select(dev, scmd_id(cmd))) {
			imm_fail(dev, DID_NO_CONNECT);
			return 0;
		}
		cmd->SCp.phase++;

		/* Phase 3 - Ready to accept a command */
	case 3:
		w_ctr(ppb, 0x0c);
		if (!(r_str(ppb) & 0x80))
			return 1;

		if (!imm_send_command(cmd))
			return 0;
		cmd->SCp.phase++;

		/* Phase 4 - Setup scatter/gather buffers */
	case 4:
		if (scsi_bufflen(cmd)) {
			cmd->SCp.buffer = scsi_sglist(cmd);
			cmd->SCp.this_residual = cmd->SCp.buffer->length;
			cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		} else {
			cmd->SCp.buffer = NULL;
			cmd->SCp.this_residual = 0;
			cmd->SCp.ptr = NULL;
		}
		cmd->SCp.buffers_residual = scsi_sg_count(cmd) - 1;
		cmd->SCp.phase++;
		if (cmd->SCp.this_residual & 0x01)
			cmd->SCp.this_residual++;
		/* Phase 5 - Pre-Data transfer stage */
	case 5:
		/* Spin lock for BUSY */
		w_ctr(ppb, 0x0c);
		if (!(r_str(ppb) & 0x80))
			return 1;

		/* Require negotiation for read requests */
		x = (r_str(ppb) & 0xb8);
		dev->rd = (x & 0x10) ? 1 : 0;
		dev->dp = (x & 0x20) ? 0 : 1;

		if ((dev->dp) && (dev->rd))
			if (imm_negotiate(dev))
				return 0;
		cmd->SCp.phase++;

		/* Phase 6 - Data transfer stage */
	case 6:
		/* Spin lock for BUSY */
		w_ctr(ppb, 0x0c);
		if (!(r_str(ppb) & 0x80))
			return 1;

		if (dev->dp) {
			retv = imm_completion(cmd);
			if (retv == -1)
				return 0;
			if (retv == 0)
				return 1;
		}
		cmd->SCp.phase++;

		/* Phase 7 - Post data transfer stage */
	case 7:
		if ((dev->dp) && (dev->rd)) {
			if ((dev->mode == IMM_NIBBLE) || (dev->mode == IMM_PS2)) {
				w_ctr(ppb, 0x4);
				w_ctr(ppb, 0xc);
				w_ctr(ppb, 0xe);
				w_ctr(ppb, 0x4);
			}
		}
		cmd->SCp.phase++;

		/* Phase 8 - Read status/message */
	case 8:
		/* Check for data overrun */
		if (imm_wait(dev) != (unsigned char) 0xb8) {
			imm_fail(dev, DID_ERROR);
			return 0;
		}
		if (imm_negotiate(dev))
			return 0;
		if (imm_in(dev, &l, 1)) {	/* read status byte */
			/* Check for optional message byte */
			if (imm_wait(dev) == (unsigned char) 0xb8)
				imm_in(dev, &h, 1);
			cmd->result = (DID_OK << 16) + (l & STATUS_MASK);
		}
		if ((dev->mode == IMM_NIBBLE) || (dev->mode == IMM_PS2)) {
			w_ctr(ppb, 0x4);
			w_ctr(ppb, 0xc);
			w_ctr(ppb, 0xe);
			w_ctr(ppb, 0x4);
		}
		return 0;	/* Finished */
		break;

	default:
		printk("imm: Invalid scsi phase\n");
	}
	return 0;
}