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
struct regstat {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,int /*<<< orphan*/ ) ; 
 int* imm ; 
 int* opcode ; 
 int /*<<< orphan*/ * rt1 ; 
 int /*<<< orphan*/  set_const (struct regstat*,int /*<<< orphan*/ ,int) ; 
 unsigned int slen ; 
 int* source ; 
 int start ; 

void pcrel_alloc(struct regstat *current,int i)
{
  u32 addr;
  alloc_reg(current,i,rt1[i]);
  addr=((start+i*2+4)&~3)+imm[i];
  if(opcode[i]==12) { // MOVA, address generation only
    set_const(current,rt1[i],addr);
  }else if((unsigned)((addr-start)>>1)<slen) {
    if(opcode[i]==9) { // MOV.W
      addr=(start+i*2+4)+imm[i];
      set_const(current,rt1[i],(s16)source[(addr-start)>>1]);
    }
    else // MOV.L
      set_const(current,rt1[i],(source[(addr-start)>>1]<<16)+source[(addr+2-start)>>1]);
  }
  else {
    // Do actual load
    //alloc_reg(current,i,MOREG);
    clear_const(current,rt1[i]);
  }
  dirty_reg(current,rt1[i]);
}