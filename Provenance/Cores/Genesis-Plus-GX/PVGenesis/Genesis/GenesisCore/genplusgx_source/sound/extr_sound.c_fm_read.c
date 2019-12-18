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
 unsigned int YM2612Read () ; 
 int /*<<< orphan*/  fm_update (unsigned int) ; 

unsigned int fm_read(unsigned int cycles, unsigned int address)
{
  /* synchronize FM chip with CPU */
  fm_update(cycles);

  /* read FM status (YM2612 only) */
  return YM2612Read();
}