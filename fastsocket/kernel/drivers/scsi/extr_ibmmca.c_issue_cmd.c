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
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IM_ATTN_REG (struct Scsi_Host*) ; 
 int IM_BUSY ; 
 int /*<<< orphan*/  IM_CMD_REG (struct Scsi_Host*) ; 
 int /*<<< orphan*/  IM_STAT_REG (struct Scsi_Host*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void issue_cmd(struct Scsi_Host *shpnt, unsigned long cmd_reg,
		      unsigned char attn_reg)
{
	unsigned long flags;
	/* must wait for attention reg not busy */
	while (1) {
		spin_lock_irqsave(shpnt->host_lock, flags);
		if (!(inb(IM_STAT_REG(shpnt)) & IM_BUSY))
			break;
		spin_unlock_irqrestore(shpnt->host_lock, flags);
	}
	/* write registers and enable system interrupts */
	outl(cmd_reg, IM_CMD_REG(shpnt));
	outb(attn_reg, IM_ATTN_REG(shpnt));
	spin_unlock_irqrestore(shpnt->host_lock, flags);
}