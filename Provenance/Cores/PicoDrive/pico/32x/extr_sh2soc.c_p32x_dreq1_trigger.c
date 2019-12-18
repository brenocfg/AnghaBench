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
 int EL_32XP ; 
 int EL_ANOMALY ; 
 int /*<<< orphan*/  dreq1_do (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  elprintf (int,char*) ; 
 TYPE_1__ msh2 ; 
 TYPE_1__ ssh2 ; 

void p32x_dreq1_trigger(void)
{
  struct dmac *mdmac = (void *)&msh2.peri_regs[0x180 / 4];
  struct dmac *sdmac = (void *)&ssh2.peri_regs[0x180 / 4];
  int hit = 0;

  elprintf(EL_32XP, "dreq1_trigger");
  if ((mdmac->dmaor & DMA_DME) && (mdmac->chan[1].chcr & 3) == DMA_DE) {
    dreq1_do(&msh2, &mdmac->chan[1]);
    hit = 1;
  }
  if ((sdmac->dmaor & DMA_DME) && (sdmac->chan[1].chcr & 3) == DMA_DE) {
    dreq1_do(&ssh2, &sdmac->chan[1]);
    hit = 1;
  }

  // debug
#if (EL_LOGMASK & (EL_32XP|EL_ANOMALY))
  {
    static int miss_count;
    if (!hit) {
      if (++miss_count == 4)
        elprintf(EL_32XP|EL_ANOMALY, "dreq1: nobody cared");
    }
    else
      miss_count = 0;
  }
#endif
  (void)hit;
}