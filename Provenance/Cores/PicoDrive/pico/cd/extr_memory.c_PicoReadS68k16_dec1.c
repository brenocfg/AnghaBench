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
typedef  int u32 ;
struct TYPE_2__ {int** word_ram1M; } ;

/* Variables and functions */
 TYPE_1__* Pico_mcd ; 

__attribute__((used)) static u32 PicoReadS68k16_dec1(u32 a)
{
  u32 d = Pico_mcd->word_ram1M[1][((a >> 1) ^ 1) & 0x1ffff];
  d |= d << 4;
  d &= ~0xf0;
  return d;
}