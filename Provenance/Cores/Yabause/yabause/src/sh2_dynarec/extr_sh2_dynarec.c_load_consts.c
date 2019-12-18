#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int isdoingcp; } ;

/* Variables and functions */
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 scalar_t__* bt ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 scalar_t__ get_final_value (int,int,int*) ; 
 TYPE_1__* regs ; 

void load_consts(signed char pre[],signed char regmap[],int i)
{
  int hr;
  // Load 32-bit regs
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG&&regmap[hr]>=0) {
      if(i==0||!((regs[i-1].isdoingcp>>hr)&1)||pre[hr]!=regmap[hr]||bt[i]) {
        if(((regs[i].isdoingcp>>hr)&1)&&regmap[hr]<64&&regmap[hr]>=0) {
          int value;
          if(get_final_value(hr,i,&value)) {
            emit_movimm(value,hr);
          }
        }
      }
    }
  }
}