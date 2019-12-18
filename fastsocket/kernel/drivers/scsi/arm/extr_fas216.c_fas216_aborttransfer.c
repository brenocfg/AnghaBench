#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ transfer_type; int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  SCp; } ;
struct TYPE_9__ {TYPE_2__ dma; TYPE_1__ scsi; int /*<<< orphan*/  host; } ;
typedef  TYPE_3__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FLUSHFIFO ; 
 int /*<<< orphan*/  fas216_checkmagic (TYPE_3__*) ; 
 int /*<<< orphan*/  fas216_cmd (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fasdma_none ; 
 scalar_t__ fasdma_real_all ; 
 scalar_t__ fasdma_real_block ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fas216_aborttransfer(FAS216_Info *info)
{
	fas216_checkmagic(info);

	if (info->dma.transfer_type == fasdma_real_all ||
	    info->dma.transfer_type == fasdma_real_block)
		info->dma.stop(info->host, &info->scsi.SCp);

	info->dma.transfer_type = fasdma_none;
	fas216_cmd(info, CMD_FLUSHFIFO);
}