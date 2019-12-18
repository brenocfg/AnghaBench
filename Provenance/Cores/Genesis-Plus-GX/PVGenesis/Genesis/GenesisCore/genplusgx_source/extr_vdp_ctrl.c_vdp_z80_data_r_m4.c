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

/* Variables and functions */
 int addr ; 
 unsigned int* fifo ; 
 scalar_t__ pending ; 
 scalar_t__* reg ; 
 unsigned int* vram ; 

__attribute__((used)) static unsigned int vdp_z80_data_r_m4(void)
{
  /* Read buffer */
  unsigned int data = fifo[0];

  /* Clear pending flag */
  pending = 0;

  /* Process next read */
  fifo[0] = vram[addr & 0x3FFF];

  /* Increment address register (TODO: check how address is incremented in Mode 4) */
  addr += (reg[15] + 1);

  /* Return data */
  return data;
}