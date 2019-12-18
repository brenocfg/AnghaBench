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
struct regstat {int* regmap; int dirty; } ;

/* Variables and functions */
 int HOST_REGS ; 

void dirty_reg(struct regstat *cur,signed char reg)
{
  int hr;
  if(reg<0) return;
  for (hr=0;hr<HOST_REGS;hr++) {
    if((cur->regmap[hr]&63)==reg) {
      cur->dirty|=1<<hr;
    }
  }
}