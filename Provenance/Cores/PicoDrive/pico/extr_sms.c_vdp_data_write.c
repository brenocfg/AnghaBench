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
struct PicoVideo {int type; int addr; scalar_t__ pending; } ;
struct TYPE_3__ {int dirtyPal; } ;
struct TYPE_4__ {unsigned char* cram; unsigned char* vramb; TYPE_1__ m; struct PicoVideo video; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 

__attribute__((used)) static void vdp_data_write(unsigned char d)
{
  struct PicoVideo *pv = &Pico.video;

  if (pv->type == 3) {
    Pico.cram[pv->addr & 0x1f] = d;
    Pico.m.dirtyPal = 1;
  } else {
    Pico.vramb[pv->addr] = d;
  }
  pv->addr = (pv->addr + 1) & 0x3fff;

  pv->pending = 0;
}