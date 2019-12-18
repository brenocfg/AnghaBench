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
struct regstat {long long u; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EAX ; 
 int EDX ; 
 int HOST_TEMPREG ; 
 long long MACH ; 
 long long MACL ; 
 long long SR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_andimm (int,int,int) ; 
 int /*<<< orphan*/  emit_div0s (int,int,int,int) ; 
 int /*<<< orphan*/  emit_imul (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movswl_reg (int,int) ; 
 int /*<<< orphan*/  emit_movzwl_reg (int,int) ; 
 int /*<<< orphan*/  emit_mul (int) ; 
 int /*<<< orphan*/  emit_multiply (int,int,int) ; 
 int /*<<< orphan*/  emit_smull (int,int,int,int) ; 
 int /*<<< orphan*/  emit_umull (int,int,int,int) ; 
 int /*<<< orphan*/  emit_zeroreg (int) ; 
 int get_reg (int /*<<< orphan*/ ,long long) ; 
 int* opcode ; 
 int* opcode2 ; 
 long long* rs1 ; 
 long long* rs2 ; 
 long long* rt1 ; 
 long long* rt2 ; 

void multdiv_assemble(int i,struct regstat *i_regs)
{
  if(opcode[i]==0) {
    if(opcode2[i]==7) // MUL.L
    {
      int s1=get_reg(i_regs->regmap,rs1[i]);
      int s2=get_reg(i_regs->regmap,rs2[i]);
      int t=get_reg(i_regs->regmap,MACL);
      if(t>=0) emit_multiply(s1,s2,t);
    }
    if(opcode2[i]==8) // CLRMAC
    {
      int t1=get_reg(i_regs->regmap,rt1[i]);
      int t2=get_reg(i_regs->regmap,rt2[i]);
      if(!(i_regs->u&(1LL<<MACH))) 
        emit_zeroreg(t1);
      if(!(i_regs->u&(1LL<<MACL))) 
        emit_zeroreg(t2);
    }
    if(opcode2[i]==9) // DIV0U
    {
      int sr=get_reg(i_regs->regmap,SR);
      emit_andimm(sr,0xfe,sr);
    }
  }
  if(opcode[i]==2) {
    if(opcode2[i]==7) // DIV0S
    {
      int s1=get_reg(i_regs->regmap,rs1[i]);
      int s2=get_reg(i_regs->regmap,rs2[i]);
      int sr=get_reg(i_regs->regmap,SR);
      int temp=get_reg(i_regs->regmap,-1);
      assert(s1>=0);
      assert(s2>=0);
      assert(sr>=0);
      emit_div0s(s1,s2,sr,temp);
    }
    if(opcode2[i]==14||opcode2[i]==15) // MULU.W / MULS.W
    {
      int s1=get_reg(i_regs->regmap,rs1[i]);
      int s2=get_reg(i_regs->regmap,rs2[i]);
      int t=get_reg(i_regs->regmap,MACL);
      #ifdef HOST_TEMPREG
      int temp=HOST_TEMPREG;
      #else
      int temp=get_reg(i_regs->regmap,-1);
      #endif
      if(t>=0) {
        assert(temp>=0);
        if(opcode2[i]==14) { // MULU.W
          emit_movzwl_reg(s1,t);
          emit_movzwl_reg(s2,temp);
        }else{ // MULS.W
          emit_movswl_reg(s1,t);
          emit_movswl_reg(s2,temp);
        }
        emit_multiply(t,temp,t);
      }
      /* DEBUG
      emit_pusha();
      emit_pushreg(t);
      emit_pushreg(t);
      emit_pushreg(s2);
      emit_pushreg(s1);
      emit_call((int)debug_multiplication);
      emit_addimm(ESP,16,ESP);
      emit_popa();*/
    }
  }
  if(opcode[i]==3) {
    int s1=get_reg(i_regs->regmap,rs1[i]);
    int s2=get_reg(i_regs->regmap,rs2[i]);
    int th=get_reg(i_regs->regmap,MACH);
    int tl=get_reg(i_regs->regmap,MACL);
    if(th>=0) {
      // DMULU.L / DMULS.L
      #if defined(__i386__) || defined(__x86_64__)
      assert(tl==EAX);
      assert(th==EDX);
      assert(s1!=EAX); // This would work only if s1 is clean or dead
      if(s1!=EAX) emit_mov(s1,EAX);
      if(opcode2[i]==5) emit_mul(s2); // DMULU.L
      if(opcode2[i]==13) emit_imul(s2); // DMULS.L
      #else
      if(opcode2[i]==5) emit_umull(s1,s2,th,tl); // DMULU.L
      if(opcode2[i]==13) emit_smull(s1,s2,th,tl); // DMULS.L
      #endif
    }else if(tl>=0) {
      // MACH is unneeded, 32-bit result only
      emit_multiply(s1,s2,tl);
    }
    /* DEBUG
    emit_pusha();
    emit_pushreg(tl);
    emit_pushreg(th);
    emit_pushreg(s2);
    emit_pushreg(s1);
    emit_call((int)debug_multiplication);
    emit_addimm(ESP,16,ESP);
    emit_popa();*/
  }
}