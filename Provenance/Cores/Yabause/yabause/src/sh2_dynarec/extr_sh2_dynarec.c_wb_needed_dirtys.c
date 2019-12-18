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
 char SR ; 
 int /*<<< orphan*/  emit_storereg (char,int) ; 
 TYPE_1__* regs ; 
 int start ; 

void wb_needed_dirtys(signed char i_regmap[],u32 i_dirty,int addr)
{
  int hr;
  int t=(addr-start)>>1;
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG) {
      if(i_regmap[hr]>=0) {
        if(i_regmap[hr]!=CCREG) {
          if((i_regmap[hr]==regs[t].regmap_entry[hr] && ((regs[t].dirty>>hr)&1)) || i_regmap[hr]==SR || i_regmap[hr]==15) {
            if((i_dirty>>hr)&1) {
              emit_storereg(i_regmap[hr],hr);
            }
          }
        }
      }
    }
  }
}