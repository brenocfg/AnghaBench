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
typedef  int u16 ;
struct TYPE_4__ {int dirtyPal; } ;
struct TYPE_5__ {unsigned int addr; int type; int* reg; } ;
struct TYPE_6__ {int* vram; int* cram; int* vsram; TYPE_1__ m; TYPE_2__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  AutoIncrement () ; 
 int /*<<< orphan*/  PDRAW_DIRTY_SPRITES ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  rendstatus ; 

__attribute__((used)) static void VideoWrite(u16 d)
{
  unsigned int a=Pico.video.addr;

  switch (Pico.video.type)
  {
    case 1: if(a&1) d=(u16)((d<<8)|(d>>8)); // If address is odd, bytes are swapped (which game needs this?)
            Pico.vram [(a>>1)&0x7fff]=d;
            if (a - ((unsigned)(Pico.video.reg[5]&0x7f) << 9) < 0x400)
              rendstatus |= PDRAW_DIRTY_SPRITES;
            break;
    case 3: Pico.m.dirtyPal = 1;
            Pico.cram [(a>>1)&0x003f]=d; break; // wraps (Desert Strike)
    case 5: Pico.vsram[(a>>1)&0x003f]=d; break;
    //default:elprintf(EL_ANOMALY, "VDP write %04x with bad type %i", d, Pico.video.type); break;
  }

  AutoIncrement();
}