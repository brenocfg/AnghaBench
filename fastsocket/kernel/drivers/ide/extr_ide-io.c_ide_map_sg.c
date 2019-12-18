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
struct scatterlist {int dummy; } ;
struct request {int dummy; } ;
struct ide_cmd {int /*<<< orphan*/  sg_nents; struct request* rq; } ;
struct TYPE_4__ {struct scatterlist* sg_table; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {int /*<<< orphan*/  queue; TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_map_sg (int /*<<< orphan*/ ,struct request*,struct scatterlist*) ; 

void ide_map_sg(ide_drive_t *drive, struct ide_cmd *cmd)
{
	ide_hwif_t *hwif = drive->hwif;
	struct scatterlist *sg = hwif->sg_table;
	struct request *rq = cmd->rq;

	cmd->sg_nents = blk_rq_map_sg(drive->queue, rq, sg);
}