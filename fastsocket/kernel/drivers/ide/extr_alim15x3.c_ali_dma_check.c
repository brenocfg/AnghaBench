#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ide_cmd {int tf_flags; } ;
struct TYPE_3__ {scalar_t__ media; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_TFLAG_WRITE ; 
 scalar_t__ ide_disk ; 
 int m5229_revision ; 

__attribute__((used)) static int ali_dma_check(ide_drive_t *drive, struct ide_cmd *cmd)
{
	if (m5229_revision < 0xC2 && drive->media != ide_disk) {
		if (cmd->tf_flags & IDE_TFLAG_WRITE)
			return 1;	/* try PIO instead of DMA */
	}
	return 0;
}