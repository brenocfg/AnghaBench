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
struct scsi_pointer {int dummy; } ;
struct TYPE_3__ {scalar_t__ dma; } ;
struct TYPE_4__ {TYPE_1__ scsi; } ;
struct cumanascsi2_info {TYPE_2__ info; scalar_t__ base; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALATCH_DIS_DMA ; 
 scalar_t__ CUMANASCSI2_ALATCH ; 
 scalar_t__ NO_DMA ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
cumanascsi_2_dma_stop(struct Scsi_Host *host, struct scsi_pointer *SCp)
{
	struct cumanascsi2_info *info = (struct cumanascsi2_info *)host->hostdata;
	if (info->info.scsi.dma != NO_DMA) {
		writeb(ALATCH_DIS_DMA, info->base + CUMANASCSI2_ALATCH);
		disable_dma(info->info.scsi.dma);
	}
}