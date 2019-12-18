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
typedef  char u64 ;
typedef  int u32 ;

/* Variables and functions */
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 char TEMPREG ; 
 int /*<<< orphan*/  emit_loadreg (char,int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_storereg (char,int) ; 
 scalar_t__ get_reg (char*,char) ; 

void wb_invalidate(signed char pre[],signed char entry[],u32 dirty, u64 u)
{
  int hr;
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG) {
      if(pre[hr]!=entry[hr]) {
        if(pre[hr]>=0) {
          if((dirty>>hr)&1) {
            if(!((u>>pre[hr])&1)) {
              int nr;
              if((nr=get_reg(entry,pre[hr]))<0) {
                emit_storereg(pre[hr],hr);
              }else{
                // Register move would overwrite another register, so write back
                if(pre[nr]>=0)
                  if(get_reg(entry,pre[nr])>=0)
                    emit_storereg(pre[hr],hr);
              }
            }
          }
        }
      }
    }
  }
  // Move from one register to another (no writeback)
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG) {
      if(pre[hr]!=entry[hr]) {
        if(pre[hr]>=0&&(pre[hr]&63)<TEMPREG) {
          int nr;
          if((nr=get_reg(entry,pre[hr]))>=0) {
            if(pre[nr]<0||get_reg(entry,pre[nr])<0) {
              emit_mov(hr,nr);
            }
          }
        }
      }
    }
  }
  // Reload registers that couldn't be directly moved
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG) {
      if(pre[hr]!=entry[hr]) {
        if(pre[hr]>=0&&(pre[hr]&63)<TEMPREG) {
          int nr;
          if((nr=get_reg(entry,pre[hr]))>=0) {
            if(pre[nr]>=0) {
              if(get_reg(entry,pre[nr])>=0) {
                emit_loadreg(pre[hr],nr);
              }
            }
          }
        }
      }
    }
  }
}