#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ni; int ri; int ti; } ;
struct TYPE_6__ {int sw_reset; scalar_t__ val; } ;
struct TYPE_5__ {int dma_enable; } ;
struct TYPE_8__ {TYPE_3__ idinten; TYPE_2__ bmod; TYPE_1__ ctrl; } ;

/* Variables and functions */
 TYPE_4__ SDMMC ; 

__attribute__((used)) static void sdmmc_host_dma_init(void)
{
    SDMMC.ctrl.dma_enable = 1;
    SDMMC.bmod.val = 0;
    SDMMC.bmod.sw_reset = 1;
    SDMMC.idinten.ni = 1;
    SDMMC.idinten.ri = 1;
    SDMMC.idinten.ti = 1;
}