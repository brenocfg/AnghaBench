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
typedef  unsigned short u16 ;
struct TYPE_5__ {unsigned short addr; unsigned char* reg; int status; } ;
struct TYPE_4__ {int dma_xfers; } ;
struct TYPE_6__ {TYPE_2__ video; TYPE_1__ m; scalar_t__ vram; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_VDPDMA ; 
 int GetDmaLength () ; 
 int /*<<< orphan*/  PDRAW_DIRTY_SPRITES ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  SekCyclesDone () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rendstatus ; 

__attribute__((used)) static void DmaFill(int data)
{
  int len;
  unsigned short a=Pico.video.addr;
  unsigned char *vr=(unsigned char *) Pico.vram;
  unsigned char high = (unsigned char) (data >> 8);
  unsigned char inc=Pico.video.reg[0xf];

  len=GetDmaLength();
  elprintf(EL_VDPDMA, "DmaFill len %i inc %i [%i]", len, inc, SekCyclesDone());

  Pico.m.dma_xfers += len;
  Pico.video.status |= 2; // dma busy

  // from Charles MacDonald's genvdp.txt:
  // Write lower byte to address specified
  vr[a] = (unsigned char) data;
  a=(u16)(a+inc);

  if (!inc) len=1;

  for (; len; len--) {
    // Write upper byte to adjacent address
    // (here we are byteswapped, so address is already 'adjacent')
    vr[a] = high;

    // Increment address register
    a=(u16)(a+inc);
  }
  // remember addr
  Pico.video.addr=a;
  // update length
  Pico.video.reg[0x13] = Pico.video.reg[0x14] = 0; // Dino Dini's Soccer (E) (by Haze)

  rendstatus |= PDRAW_DIRTY_SPRITES;
}