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
 TYPE_1__ Pico ; 

__attribute__((used)) static int GetDmaLength(void)
{
  struct PicoVideo *pvid=&Pico.video;
  int len=0;
  // 16-bit words to transfer:
  len =pvid->reg[0x13];
  len|=pvid->reg[0x14]<<8;
  // Charles MacDonald:
  if(!len) len = 0xffff;
  return len;
}