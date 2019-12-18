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
struct TYPE_2__ {int* regs; } ;

/* Variables and functions */
 TYPE_1__ Pico32x ; 
 int m68k_read16 (int) ; 

__attribute__((used)) static u32 PicoRead16_bank(u32 a)
{
  a = (Pico32x.regs[4 / 2] << 20) | (a & 0xfffff);
  return m68k_read16(a);
}