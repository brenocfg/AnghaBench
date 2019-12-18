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
typedef  size_t u16 ;
struct TYPE_5__ {size_t addr; unsigned char* reg; int status; } ;
struct TYPE_4__ {int dma_xfers; } ;
struct TYPE_6__ {TYPE_2__ video; TYPE_1__ m; scalar_t__ vram; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_VDPDMA ; 
 int /*<<< orphan*/  PDRAW_DIRTY_SPRITES ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rendstatus ; 

__attribute__((used)) static void DmaCopy(int len)
{
  u16 a=Pico.video.addr;
  unsigned char *vr = (unsigned char *) Pico.vram;
  unsigned char *vrs;
  unsigned char inc=Pico.video.reg[0xf];
  int source;
  elprintf(EL_VDPDMA, "DmaCopy len %i [%i]", len, SekCyclesDone());

  Pico.m.dma_xfers += len;
  Pico.video.status |= 2; // dma busy

  source =Pico.video.reg[0x15];
  source|=Pico.video.reg[0x16]<<8;
  vrs=vr+source;

  if (source+len > 0x10000) len=0x10000-source; // clip??

  for (; len; len--)
  {
    vr[a] = *vrs++;
    // AutoIncrement
    a=(u16)(a+inc);
  }
  // remember addr
  Pico.video.addr=a;
  rendstatus |= PDRAW_DIRTY_SPRITES;
}