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
struct TYPE_3__ {unsigned int addr; int type; } ;
struct TYPE_4__ {unsigned int* vram; unsigned int* cram; unsigned int* vsram; TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  AutoIncrement () ; 
 int /*<<< orphan*/  EL_ANOMALY ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static unsigned int VideoRead(void)
{
  unsigned int a=0,d=0;

  a=Pico.video.addr; a>>=1;

  switch (Pico.video.type)
  {
    case 0: d=Pico.vram [a&0x7fff]; break;
    case 8: d=Pico.cram [a&0x003f]; break;
    case 4: d=Pico.vsram[a&0x003f]; break;
    default:elprintf(EL_ANOMALY, "VDP read with bad type %i", Pico.video.type); break;
  }

  AutoIncrement();
  return d;
}