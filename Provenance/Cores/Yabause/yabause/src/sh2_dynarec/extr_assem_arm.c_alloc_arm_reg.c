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
typedef  char u32 ;
struct regstat {char* regmap; int dirty; int isdoingcp; } ;

/* Variables and functions */
 int EXCLUDE_REG ; 
 int HOST_REGS ; 

void alloc_arm_reg(struct regstat *cur,int i,signed char reg,char hr)
{
  int n;
  u32 dirty=0;
  
  // see if it's already allocated (and dealloc it)
  for(n=0;n<HOST_REGS;n++)
  {
    if(n!=EXCLUDE_REG&&cur->regmap[n]==reg) {
      dirty=(cur->dirty>>n)&1;
      cur->regmap[n]=-1;
    }
  }
  
  cur->regmap[hr]=reg;
  cur->dirty&=~(1<<hr);
  cur->dirty|=dirty<<hr;
  cur->isdoingcp&=~(1<<hr);
}