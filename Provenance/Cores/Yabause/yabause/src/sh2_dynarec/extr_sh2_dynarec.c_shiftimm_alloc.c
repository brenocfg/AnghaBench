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
struct regstat {long long u; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR ; 
 long long TBIT ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,int /*<<< orphan*/ ) ; 
 int* opcode ; 
 int* opcode2 ; 
 int* opcode3 ; 
 int /*<<< orphan*/ * rs1 ; 
 int /*<<< orphan*/ * rs2 ; 
 int /*<<< orphan*/ * rt1 ; 

void shiftimm_alloc(struct regstat *current,int i)
{
  clear_const(current,rs1[i]);
  clear_const(current,rt1[i]);
  alloc_reg(current,i,rs1[i]);
  alloc_reg(current,i,rt1[i]);
  dirty_reg(current,rt1[i]);
  if(opcode[i]==4) {
    if(opcode2[i]<6) { // SHLL/SHAL/SHLR/SHAR/ROTL/ROTCL/ROTR/ROTCR
      if(opcode2[i]<4||opcode3[i]<2) {
        // SHL/SHA/ROT don't need T bit as a source, only a destination
        if(!(current->u&(1LL<<TBIT))) {
          alloc_reg(current,i,SR);
          dirty_reg(current,SR);
        }
      }
      else {
        alloc_reg(current,i,SR); // ROTCL/ROTCR always need T bit
        dirty_reg(current,SR);
      }
    }
  }
  if(opcode[i]==2&opcode2[i]==13) { // XTRCT
    clear_const(current,rs2[i]);
    alloc_reg(current,i,rs2[i]);
  }
}