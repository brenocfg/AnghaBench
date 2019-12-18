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
 int /*<<< orphan*/  EAX ; 
 int /*<<< orphan*/  EDX ; 
 long long MACH ; 
 long long MACL ; 
 long long SR ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,long long) ; 
 int /*<<< orphan*/  alloc_reg_temp (struct regstat*,int,int) ; 
 int /*<<< orphan*/  alloc_x86_reg (struct regstat*,int,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,long long) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,long long) ; 
 int* minimum_free_regs ; 
 int* opcode ; 
 int* opcode2 ; 
 long long* rs1 ; 
 long long* rs2 ; 

void multdiv_alloc(struct regstat *current,int i)
{
  //printf("%x: eax=%d ecx=%d edx=%d ebx=%d ebp=%d esi=%d edi=%d\n",start+i*2,current->regmap[0],current->regmap[1],current->regmap[2],current->regmap[3],current->regmap[5],current->regmap[6],current->regmap[7]);
  if(opcode[i]==0) {
    if(opcode2[i]==7) // MUL.L
    {
      clear_const(current,rs1[i]);
      clear_const(current,rs2[i]);
      clear_const(current,MACL);
      alloc_reg(current,i,rs1[i]);
      alloc_reg(current,i,rs2[i]);
      alloc_reg(current,i,MACL);
      dirty_reg(current,MACL);
    }
    if(opcode2[i]==8) // CLRMAC
    {
      clear_const(current,MACH);
      clear_const(current,MACL);
      alloc_reg(current,i,MACH);
      alloc_reg(current,i,MACL);
      dirty_reg(current,MACH);
      dirty_reg(current,MACL);
    }
    if(opcode2[i]==9) // DIV0U
    {
      alloc_reg(current,i,SR);
      dirty_reg(current,SR);
    }
  }
  if(opcode[i]==2) {
    if(opcode2[i]==7) // DIV0S
    {
      clear_const(current,rs1[i]); // Is this necessary?
      clear_const(current,rs2[i]); // Is this necessary?
      alloc_reg(current,i,rs1[i]);
      alloc_reg(current,i,rs2[i]);
      alloc_reg(current,i,SR);
      dirty_reg(current,SR);
      #if defined(__i386__) || defined(__x86_64__)
      //#ifdef NEEDS_TEMP
      alloc_reg_temp(current,i,-1);
      minimum_free_regs[i]=1;
      #endif
    }
    if(opcode2[i]==14||opcode2[i]==15) // MULU.W / MULS.W
    {
      clear_const(current,rs1[i]);
      clear_const(current,rs2[i]);
      clear_const(current,MACL);
      alloc_reg(current,i,rs1[i]);
      alloc_reg(current,i,rs2[i]);
      alloc_reg(current,i,MACL);
      dirty_reg(current,MACL);
      //#ifdef NEEDS_TEMP
      alloc_reg_temp(current,i,-1);
      minimum_free_regs[i]=1;
    }
  }
  if(opcode[i]==3) {
    // DMULU.L / DMULS.L
    #if defined(__i386__) || defined(__x86_64__)
    if(!(current->u&(1LL<<MACH))) {
      alloc_x86_reg(current,i,MACH,EDX); // Don't need to alloc MACH if it's unneeded
      current->u&=~(1LL<<MACL); // But if it is, then assume MACL is needed since it will be overwritten
    }
    alloc_x86_reg(current,i,MACL,EAX);
    #else
    if(!(current->u&(1LL<<MACH))) {
      alloc_reg(current,i,MACH);
      current->u&=~(1LL<<MACL);
    }
    alloc_reg(current,i,MACL);
    #endif
    clear_const(current,rs1[i]);
    clear_const(current,rs2[i]);
    clear_const(current,MACH);
    clear_const(current,MACL);
    alloc_reg(current,i,rs1[i]);
    alloc_reg(current,i,rs2[i]);
    dirty_reg(current,MACH);
    dirty_reg(current,MACL);
  }
}