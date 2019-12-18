#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_4__ {int /*<<< orphan*/  command; } ;
struct ide_cmd {int tf_flags; TYPE_1__ tf; int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {scalar_t__ mult_count; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PROT_DMA ; 
 int /*<<< orphan*/  ATA_PROT_PIO ; 
 int IDE_TFLAG_LBA48 ; 
 int IDE_TFLAG_MULTI_PIO ; 
 int IDE_TFLAG_WRITE ; 
 int /*<<< orphan*/ * ide_rw_cmds ; 

__attribute__((used)) static void ide_tf_set_cmd(ide_drive_t *drive, struct ide_cmd *cmd, u8 dma)
{
	u8 index, lba48, write;

	lba48 = (cmd->tf_flags & IDE_TFLAG_LBA48) ? 2 : 0;
	write = (cmd->tf_flags & IDE_TFLAG_WRITE) ? 1 : 0;

	if (dma) {
		cmd->protocol = ATA_PROT_DMA;
		index = 8;
	} else {
		cmd->protocol = ATA_PROT_PIO;
		if (drive->mult_count) {
			cmd->tf_flags |= IDE_TFLAG_MULTI_PIO;
			index = 0;
		} else
			index = 4;
	}

	cmd->tf.command = ide_rw_cmds[index + lba48 + write];
}