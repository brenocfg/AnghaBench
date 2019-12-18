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
struct PicoVideo {size_t addr; scalar_t__ pending; } ;
struct TYPE_2__ {unsigned char* vramb; struct PicoVideo video; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 

__attribute__((used)) static unsigned char vdp_data_read(void)
{
  struct PicoVideo *pv = &Pico.video;
  unsigned char d;

  d = Pico.vramb[pv->addr];
  pv->addr = (pv->addr + 1) & 0x3fff;
  pv->pending = 0;
  return d;
}