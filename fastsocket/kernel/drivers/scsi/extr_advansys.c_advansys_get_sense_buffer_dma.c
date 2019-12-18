#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dma_handle; } ;
struct scsi_cmnd {TYPE_2__ SCp; int /*<<< orphan*/  sense_buffer; TYPE_1__* device; } ;
struct asc_board {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct asc_board* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le32 advansys_get_sense_buffer_dma(struct scsi_cmnd *scp)
{
	struct asc_board *board = shost_priv(scp->device->host);
	scp->SCp.dma_handle = dma_map_single(board->dev, scp->sense_buffer,
					     SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	dma_cache_sync(board->dev, scp->sense_buffer,
		       SCSI_SENSE_BUFFERSIZE, DMA_FROM_DEVICE);
	return cpu_to_le32(scp->SCp.dma_handle);
}