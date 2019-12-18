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
 int EXCLUDE_REG ; 
 int HOST_REGS ; 

signed char get_alt_reg(signed char regmap[],int r)
{
  int hr;
  for (hr=HOST_REGS-1;hr>=0;hr--) if(hr!=EXCLUDE_REG&&regmap[hr]==r) return hr;
  return -1;
}