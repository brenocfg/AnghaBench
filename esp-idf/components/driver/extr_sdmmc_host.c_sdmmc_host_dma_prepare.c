#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdmmc_desc_t ;
struct TYPE_5__ {int enable; int fb; } ;
struct TYPE_4__ {int dma_enable; int use_internal_dma; } ;
struct TYPE_6__ {size_t bytcnt; size_t blksiz; TYPE_2__ bmod; TYPE_1__ ctrl; int /*<<< orphan*/ * dbaddr; } ;

/* Variables and functions */
 TYPE_3__ SDMMC ; 
 int /*<<< orphan*/  sdmmc_host_dma_resume () ; 

void sdmmc_host_dma_prepare(sdmmc_desc_t* desc, size_t block_size, size_t data_size)
{
    // Set size of data and DMA descriptor pointer
    SDMMC.bytcnt = data_size;
    SDMMC.blksiz = block_size;
    SDMMC.dbaddr = desc;

    // Enable everything needed to use DMA
    SDMMC.ctrl.dma_enable = 1;
    SDMMC.ctrl.use_internal_dma = 1;
    SDMMC.bmod.enable = 1;
    SDMMC.bmod.fb = 1;
    sdmmc_host_dma_resume();
}