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
 long long mcd_m68k_cycle_mult ; 

unsigned int pcd_cycles_m68k_to_s68k(unsigned int c)
{
  return (long long)c * mcd_m68k_cycle_mult >> 16;
}