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
struct PicoVideo {int* reg; } ;
struct TYPE_2__ {struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  DmaCopy (int) ; 
 int /*<<< orphan*/  DmaSlow (int) ; 
 int GetDmaLength () ; 
 TYPE_1__ Pico ; 

__attribute__((used)) static void CommandDma(void)
{
  struct PicoVideo *pvid=&Pico.video;
  int len=0,method=0;

  if ((pvid->reg[1]&0x10)==0) return; // DMA not enabled

  len=GetDmaLength();

  method=pvid->reg[0x17]>>6;
  if (method< 2) DmaSlow(len); // 68000 to VDP
  if (method==3) DmaCopy(len); // VRAM Copy
}