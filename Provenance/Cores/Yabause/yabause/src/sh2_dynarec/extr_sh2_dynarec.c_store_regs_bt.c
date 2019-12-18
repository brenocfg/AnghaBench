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
struct TYPE_2__ {char* regmap_entry; int dirty; } ;

/* Variables and functions */
 char CCREG ; 
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 int /*<<< orphan*/  emit_storereg (char,int) ; 
 scalar_t__ internal_branch (int) ; 
 TYPE_1__* regs ; 
 int start ; 
 char* unneeded_reg ; 
 int /*<<< orphan*/  wb_dirtys (char*,int) ; 

void store_regs_bt(signed char i_regmap[],u32 i_dirty,int addr)
{
  if(internal_branch(addr))
  {
    int t=(addr-start)>>1;
    int hr;
    for(hr=0;hr<HOST_REGS;hr++) {
      if(hr!=EXCLUDE_REG) {
        if(i_regmap[hr]>=0 && i_regmap[hr]!=CCREG) {
          if(i_regmap[hr]!=regs[t].regmap_entry[hr] || !((regs[t].dirty>>hr)&1) ) {
            if((i_dirty>>hr)&1) {
              if(!((unneeded_reg[t]>>i_regmap[hr])&1)) {
                emit_storereg(i_regmap[hr],hr);
              }
            }
          }
        }
      }
    }
  }
  else
  {
    // Branch out of this block, write out all dirty regs
    wb_dirtys(i_regmap,i_dirty);
  }
}