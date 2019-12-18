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
typedef  int u32 ;

/* Variables and functions */
 char CCREG ; 
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 int /*<<< orphan*/  emit_storereg (char,int) ; 

void wb_dirtys(signed char i_regmap[],u32 i_dirty)
{
  int hr;
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG) {
      if(i_regmap[hr]>=0) {
        if(i_regmap[hr]!=CCREG) {
          if((i_dirty>>hr)&1) {
            emit_storereg(i_regmap[hr],hr);
          }
        }
      }
    }
  }
}