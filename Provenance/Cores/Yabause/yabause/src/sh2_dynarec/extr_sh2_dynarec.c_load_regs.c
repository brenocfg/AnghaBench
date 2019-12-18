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

/* Variables and functions */
 int EXCLUDE_REG ; 
 int HOST_REGS ; 
 int SR ; 
 int TBIT ; 
 int /*<<< orphan*/  emit_loadreg (char,int) ; 

void load_regs(signed char entry[],signed char regmap[],int rs1,int rs2,int rs3)
{
  int hr;
  if(rs1==TBIT) rs1=SR;
  if(rs2==TBIT) rs2=SR;
  if(rs3==TBIT) rs3=SR;
  // Load 32-bit regs
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG&&regmap[hr]>=0) {
      if(entry[hr]!=regmap[hr]) {
        if(regmap[hr]==rs1||regmap[hr]==rs2||regmap[hr]==rs3)
        {
          emit_loadreg(regmap[hr],hr);
        }
      }
    }
  }
}