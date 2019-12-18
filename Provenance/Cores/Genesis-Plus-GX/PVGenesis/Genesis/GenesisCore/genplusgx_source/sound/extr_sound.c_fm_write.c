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
 int /*<<< orphan*/  YM_Write (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fm_update (unsigned int) ; 

void fm_write(unsigned int cycles, unsigned int address, unsigned int data)
{
  /* synchronize FM chip with CPU (on data port write only) */
  if (address & 1)
  {
    fm_update(cycles);
  }
  
  /* write FM register */
  YM_Write(address, data);
}