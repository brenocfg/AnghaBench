#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int uint16 ;

/* Variables and functions */
 int addr ; 
 scalar_t__ pending ; 
 scalar_t__* reg ; 
 int /*<<< orphan*/ * vram ; 

__attribute__((used)) static unsigned int vdp_68k_data_r_m4(void)
{
  /* VRAM address (interleaved format) */
  int index = ((addr << 1) & 0x3FC) | ((addr & 0x200) >> 8) | (addr & 0x3C00);

  /* Clear pending flag */
  pending = 0;

  /* Increment address register (TODO: check how address is incremented in Mode 4) */
  addr += (reg[15] + 1);

  /* Read VRAM data */
  return *(uint16 *) &vram[index];
}