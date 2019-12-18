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
struct ide_cmd {int tf_flags; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 int IDE_TFLAG_WRITE ; 

__attribute__((used)) static int trm290_dma_check(ide_drive_t *drive, struct ide_cmd *cmd)
{
	if (cmd->tf_flags & IDE_TFLAG_WRITE) {
#ifdef TRM290_NO_DMA_WRITES
		/* always use PIO for writes */
		return 1;
#endif
	}
	return 0;
}