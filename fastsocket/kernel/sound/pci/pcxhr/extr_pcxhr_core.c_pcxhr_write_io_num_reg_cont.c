#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcxhr_rmh {unsigned int* cmd; int cmd_len; } ;
struct pcxhr_mgr {unsigned int io_num_reg_cont; int /*<<< orphan*/  msg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ACCESS_IO_WRITE ; 
 unsigned int IO_NUM_REG_CONT ; 
 int /*<<< orphan*/  pcxhr_init_rmh (struct pcxhr_rmh*,int /*<<< orphan*/ ) ; 
 int pcxhr_send_msg_nolock (struct pcxhr_mgr*,struct pcxhr_rmh*) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pcxhr_write_io_num_reg_cont(struct pcxhr_mgr *mgr, unsigned int mask,
				unsigned int value, int *changed)
{
	struct pcxhr_rmh rmh;
	unsigned long flags;
	int err;

	spin_lock_irqsave(&mgr->msg_lock, flags);
	if ((mgr->io_num_reg_cont & mask) == value) {
		snd_printdd("IO_NUM_REG_CONT mask %x already is set to %x\n",
			    mask, value);
		if (changed)
			*changed = 0;
		spin_unlock_irqrestore(&mgr->msg_lock, flags);
		return 0;	/* already programmed */
	}
	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
	rmh.cmd[0] |= IO_NUM_REG_CONT;
	rmh.cmd[1]  = mask;
	rmh.cmd[2]  = value;
	rmh.cmd_len = 3;
	err = pcxhr_send_msg_nolock(mgr, &rmh);
	if (err == 0) {
		mgr->io_num_reg_cont &= ~mask;
		mgr->io_num_reg_cont |= value;
		if (changed)
			*changed = 1;
	}
	spin_unlock_irqrestore(&mgr->msg_lock, flags);
	return err;
}