#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct PicoVideo {int pending; int* reg; int addr; unsigned char type; } ;
struct TYPE_2__ {struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_IO ; 
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,unsigned char,int) ; 

__attribute__((used)) static void vdp_ctl_write(unsigned char d)
{
  struct PicoVideo *pv = &Pico.video;

  if (pv->pending) {
    if ((d >> 6) == 2) {
      pv->reg[d & 0x0f] = pv->addr;
      elprintf(EL_IO, "  VDP r%02x=%02x", d & 0x0f, pv->addr & 0xff);
    }
    pv->type = d >> 6;
    pv->addr &= 0x00ff;
    pv->addr |= (d & 0x3f) << 8;
  } else {
    pv->addr &= 0x3f00;
    pv->addr |= d;
  }
  pv->pending ^= 1;
}