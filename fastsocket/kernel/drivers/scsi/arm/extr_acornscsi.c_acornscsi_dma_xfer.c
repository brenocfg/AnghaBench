#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ direction; int /*<<< orphan*/  xfer_length; int /*<<< orphan*/  xfer_start; int /*<<< orphan*/  xfer_ptr; scalar_t__ xfer_required; } ;
struct TYPE_6__ {TYPE_1__ dma; } ;
typedef  TYPE_2__ AS_Host ;

/* Variables and functions */
 scalar_t__ DMA_IN ; 
 int /*<<< orphan*/  acornscsi_data_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void acornscsi_dma_xfer(AS_Host *host)
{
    host->dma.xfer_required = 0;

    if (host->dma.direction == DMA_IN)
	acornscsi_data_read(host, host->dma.xfer_ptr,
				host->dma.xfer_start, host->dma.xfer_length);
}