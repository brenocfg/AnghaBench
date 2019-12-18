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
 int HOST_REGS ; 

void clear_all_regs(signed char regmap[])
{
  int hr;
  for (hr=0;hr<HOST_REGS;hr++) regmap[hr]=-1;
}