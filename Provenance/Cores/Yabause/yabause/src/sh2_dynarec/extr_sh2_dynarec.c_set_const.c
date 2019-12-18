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
typedef  int u64 ;
struct regstat {char* regmap; int isdoingcp; int* cpmap; } ;

/* Variables and functions */
 int HOST_REGS ; 

void set_const(struct regstat *cur,signed char reg,u64 value)
{
  int hr;
  if(reg<0) return;
  for (hr=0;hr<HOST_REGS;hr++) {
    if(cur->regmap[hr]==reg) {
      cur->isdoingcp|=1<<hr;
      cur->cpmap[hr]=value;
    }
    else if((cur->regmap[hr]^64)==reg) {
      cur->isdoingcp|=1<<hr;
      cur->cpmap[hr]=value>>32;
    }
  }
}