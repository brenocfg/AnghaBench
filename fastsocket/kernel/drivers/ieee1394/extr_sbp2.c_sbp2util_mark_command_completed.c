#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sbp2_lu {int /*<<< orphan*/  cmd_orb_completed; TYPE_4__* ud; } ;
struct sbp2_command_info {int /*<<< orphan*/  list; TYPE_5__* Current_SCpnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  sc_data_direction; } ;
struct TYPE_10__ {TYPE_3__* ne; } ;
struct TYPE_9__ {TYPE_2__* host; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_1__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sg_count (TYPE_5__*) ; 
 int /*<<< orphan*/  scsi_sglist (TYPE_5__*) ; 

__attribute__((used)) static void sbp2util_mark_command_completed(struct sbp2_lu *lu,
					    struct sbp2_command_info *cmd)
{
	if (scsi_sg_count(cmd->Current_SCpnt))
		dma_unmap_sg(lu->ud->ne->host->device.parent,
			     scsi_sglist(cmd->Current_SCpnt),
			     scsi_sg_count(cmd->Current_SCpnt),
			     cmd->Current_SCpnt->sc_data_direction);
	list_move_tail(&cmd->list, &lu->cmd_orb_completed);
}