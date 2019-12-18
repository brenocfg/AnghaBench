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
typedef  int u32 ;
struct TYPE_2__ {int isdoingcp; } ;

/* Variables and functions */
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 int** cpmap ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 TYPE_1__* regs ; 

void load_all_consts(signed char regmap[],u32 dirty,int i)
{
  int hr;
  // Load 32-bit regs
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG&&regmap[hr]>=0&&((dirty>>hr)&1)) {
      if(((regs[i].isdoingcp>>hr)&1)&&regmap[hr]<64&&regmap[hr]>=0) {
        int value=cpmap[i][hr];
        emit_movimm(value,hr);
      }
    }
  }
}