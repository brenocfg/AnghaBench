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
 int /*<<< orphan*/  ESP ; 
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 int count_bits (int) ; 
 int /*<<< orphan*/  emit_addimm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_popreg (int) ; 
 scalar_t__ slave ; 

void restore_regs(u32 reglist)
{
  int hr;
  reglist&=0x7; // only save the caller-save registers, %eax, %ecx, %edx
  int count=count_bits(reglist);
  if(slave) emit_addimm(ESP,(4-count)*4,ESP);
  else emit_addimm(ESP,(5-count)*4,ESP);
  if(count) {
    for(hr=HOST_REGS-1;hr>=0;hr--) {
      if(hr!=EXCLUDE_REG) {
        if((reglist>>hr)&1) {
          emit_popreg(hr);
        }
      }
    }
  }
}