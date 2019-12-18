#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ide_cmd {int tf_flags; int nbytes; int nleft; scalar_t__ protocol; } ;
struct TYPE_4__ {int mult_count; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_PROT_PIO ; 
 int IDE_TFLAG_FS ; 
 int IDE_TFLAG_MULTI_PIO ; 
 int IDE_TFLAG_WRITE ; 
 scalar_t__ SECTOR_SIZE ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ide_error_cmd(ide_drive_t *drive, struct ide_cmd *cmd)
{
	if (cmd->tf_flags & IDE_TFLAG_FS) {
		int nr_bytes = cmd->nbytes - cmd->nleft;

		if (cmd->protocol == ATA_PROT_PIO &&
		    ((cmd->tf_flags & IDE_TFLAG_WRITE) || cmd->nleft == 0)) {
			if (cmd->tf_flags & IDE_TFLAG_MULTI_PIO)
				nr_bytes -= drive->mult_count << 9;
			else
				nr_bytes -= SECTOR_SIZE;
		}

		if (nr_bytes > 0)
			ide_complete_rq(drive, 0, nr_bytes);
	}
}