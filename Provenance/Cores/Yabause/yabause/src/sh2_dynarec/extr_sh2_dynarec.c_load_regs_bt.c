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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {char* regmap_entry; } ;

/* Variables and functions */
 char CCREG ; 
 int EXCLUDE_REG ; 
 size_t HOST_CCREG ; 
 int HOST_REGS ; 
 char TEMPREG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_loadreg (char,int) ; 
 int /*<<< orphan*/  emit_storereg (char,size_t) ; 
 scalar_t__ internal_branch (int) ; 
 TYPE_1__* regs ; 
 int start ; 

void load_regs_bt(signed char i_regmap[],u32 i_dirty,int addr)
{
  //if(addr>=start && addr<(start+slen*4))
  if(internal_branch(addr))
  {
    int t=(addr-start)>>1;
    int hr;
    // Store the cycle count before loading something else
    if(i_regmap[HOST_CCREG]!=CCREG) {
      assert(i_regmap[HOST_CCREG]==-1);
    }
    if(regs[t].regmap_entry[HOST_CCREG]!=CCREG) {
      emit_storereg(CCREG,HOST_CCREG);
    }
    // Load 32-bit regs
    for(hr=0;hr<HOST_REGS;hr++) {
      if(hr!=EXCLUDE_REG&&regs[t].regmap_entry[hr]>=0&&regs[t].regmap_entry[hr]<TEMPREG) {
        if(i_regmap[hr]!=regs[t].regmap_entry[hr] ) {
          if(regs[t].regmap_entry[hr]!=CCREG)
          {
            emit_loadreg(regs[t].regmap_entry[hr],hr);
          }
        }
      }
    }
  }
}