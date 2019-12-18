#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dmac {int dmaor; TYPE_4__* chan; } ;
struct TYPE_6__ {int chcr; } ;
struct TYPE_5__ {int /*<<< orphan*/ * peri_regs; } ;

/* Variables and functions */
 int DMA_DE ; 
 int DMA_DME ; 
 int /*<<< orphan*/  EL_32XP ; 
 int /*<<< orphan*/  dreq0_do (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ msh2 ; 
 TYPE_1__ ssh2 ; 

void p32x_dreq0_trigger(void)
{
  struct dmac *mdmac = (void *)&msh2.peri_regs[0x180 / 4];
  struct dmac *sdmac = (void *)&ssh2.peri_regs[0x180 / 4];

  elprintf(EL_32XP, "dreq0_trigger");
  if ((mdmac->dmaor & DMA_DME) && (mdmac->chan[0].chcr & 3) == DMA_DE) {
    dreq0_do(&msh2, &mdmac->chan[0]);
  }
  if ((sdmac->dmaor & DMA_DME) && (sdmac->chan[0].chcr & 3) == DMA_DE) {
    dreq0_do(&ssh2, &sdmac->chan[0]);
  }
}