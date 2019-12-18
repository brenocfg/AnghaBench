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
struct TYPE_5__ {int dma_xfers; } ;
struct TYPE_4__ {int* reg; int type; int status; } ;
struct TYPE_6__ {TYPE_2__ m; TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_VDPDMA ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int* dma_bsycles ; 
 int* dma_timings ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int /*<<< orphan*/ ) ; 

int CheckDMA(void)
{
  int burn = 0, xfers_can, dma_op = Pico.video.reg[0x17]>>6; // see gens for 00 and 01 modes
  int xfers = Pico.m.dma_xfers;
  int dma_op1;

  if(!(dma_op&2)) dma_op = (Pico.video.type==1) ? 0 : 1; // setting dma_timings offset here according to Gens
  dma_op1 = dma_op;
  if(Pico.video.reg[12] & 1) dma_op |= 4; // 40 cell mode?
  if(!(Pico.video.status&8)&&(Pico.video.reg[1]&0x40)) dma_op|=8; // active display?
  xfers_can = dma_timings[dma_op];
  if(xfers <= xfers_can)
  {
    if(dma_op&2) Pico.video.status&=~2; // dma no longer busy
    else {
      burn = xfers * dma_bsycles[dma_op] >> 8; // have to be approximate because can't afford division..
    }
    Pico.m.dma_xfers = 0;
  } else {
    if(!(dma_op&2)) burn = 488;
    Pico.m.dma_xfers -= xfers_can;
  }

  elprintf(EL_VDPDMA, "~Dma %i op=%i can=%i burn=%i [%i]", Pico.m.dma_xfers, dma_op1, xfers_can, burn, SekCyclesDone());
  //dprintf("~aim: %i, cnt: %i", SekCycleAim, SekCycleCnt);
  return burn;
}