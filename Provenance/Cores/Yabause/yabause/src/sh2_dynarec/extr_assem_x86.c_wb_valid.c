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
typedef  int u32 ;

/* Variables and functions */
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 int TBIT ; 
 int /*<<< orphan*/  emit_storereg (int,int) ; 

void wb_valid(signed char pre[],signed char entry[],u32 dirty_pre,u32 dirty,u64 u)
{
  //if(dirty_pre==dirty) return;
  int hr,reg,new_hr;
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG) {
      reg=pre[hr];
      if(((~u)>>(reg&63))&1) {
        if(reg>=0) {
          if(((dirty_pre&~dirty)>>hr)&1) {
            if(reg>=0&&reg<TBIT) {
              emit_storereg(reg,hr);
            }
          }
        }
      }
    }
  }
}