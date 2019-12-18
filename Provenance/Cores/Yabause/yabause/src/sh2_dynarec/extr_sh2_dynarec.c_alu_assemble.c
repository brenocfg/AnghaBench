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
 long long SR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_add (char,char,char) ; 
 int /*<<< orphan*/  emit_addc (char,char,char) ; 
 int /*<<< orphan*/  emit_and (char,char,char) ; 
 int /*<<< orphan*/  emit_cmpeq (char,char,char,char) ; 
 int /*<<< orphan*/  emit_cmpge (char,char,char,char) ; 
 int /*<<< orphan*/  emit_cmpgt (char,char,char,char) ; 
 int /*<<< orphan*/  emit_cmphi (char,char,char,char) ; 
 int /*<<< orphan*/  emit_cmphs (char,char,char,char) ; 
 int /*<<< orphan*/  emit_cmppl (char,char,char) ; 
 int /*<<< orphan*/  emit_cmppz (char,char) ; 
 int /*<<< orphan*/  emit_cmpstr (char,char,char,char) ; 
 int /*<<< orphan*/  emit_dt (char,char) ; 
 int /*<<< orphan*/  emit_loadreg (long long,int) ; 
 int /*<<< orphan*/  emit_neg (int,int) ; 
 int /*<<< orphan*/  emit_negc (int,int,int) ; 
 int /*<<< orphan*/  emit_not (int,int) ; 
 int /*<<< orphan*/  emit_or (char,char,char) ; 
 int /*<<< orphan*/  emit_rorimm (int,int,int) ; 
 int /*<<< orphan*/  emit_sh2tst (char,char,char,char) ; 
 int /*<<< orphan*/  emit_sub (char,char,char) ; 
 int /*<<< orphan*/  emit_subc (char,char,char) ; 
 int /*<<< orphan*/  emit_swapb (int,int) ; 
 int /*<<< orphan*/  emit_xor (char,char,char) ; 
 void* get_reg (int /*<<< orphan*/ ,long long) ; 
 int* opcode ; 
 int* opcode2 ; 
 long long* rs1 ; 
 long long* rs2 ; 
 long long* rt1 ; 

void alu_assemble(int i,struct regstat *i_regs)
{
  if(opcode[i]==2) {
    if(opcode2[i]>=9&&opcode2[i]<=11) { // AND/XOR/OR
      signed char s,t;
      s=get_reg(i_regs->regmap,rs1[i]);
      t=get_reg(i_regs->regmap,rt1[i]);
      //assert(s>=0);
      if(t>=0) {
        if(opcode2[i]==9) emit_and(s,t,t);
        if(opcode2[i]==10) emit_xor(rs1[i]>=0?s:t,t,t);
        if(opcode2[i]==11) emit_or(s,t,t);
      }
    }
    else
    {
      signed char s1,s2,sr,temp;
      s1=get_reg(i_regs->regmap,rs1[i]);
      s2=get_reg(i_regs->regmap,rs2[i]);
      sr=get_reg(i_regs->regmap,SR);
      temp=get_reg(i_regs->regmap,-1);
      assert(s1>=0);
      assert(s2>=0);
      assert(sr>=0);
      assert(temp>=0); // Not needed for TST on ARM?
      if(opcode2[i]==8) { // TST
        emit_sh2tst(s1,s2,sr,temp);
      }
      else if(opcode2[i]==12) { // CMP/STR
        emit_cmpstr(s1,s2,sr,temp);
      }
    }
  }
  if(opcode[i]==3) { // ADD/SUB
    if(opcode2[i]<8) { // CMP
      signed char s1,s2,sr,temp;
      s1=get_reg(i_regs->regmap,rs1[i]);
      s2=get_reg(i_regs->regmap,rs2[i]);
      sr=get_reg(i_regs->regmap,SR);
      temp=get_reg(i_regs->regmap,-1);
      assert(s1>=0);
      assert(s2>=0);
      assert(temp>=0);
      if(opcode2[i]==0) emit_cmpeq(s1,s2,sr,temp);
      if(opcode2[i]==2) emit_cmphs(s1,s2,sr,temp);
      if(opcode2[i]==3) emit_cmpge(s1,s2,sr,temp);
      if(opcode2[i]==6) emit_cmphi(s1,s2,sr,temp);
      if(opcode2[i]==7) emit_cmpgt(s1,s2,sr,temp);
    }
    else
    {
      signed char s,t,sr,temp;
      t=get_reg(i_regs->regmap,rt1[i]);
      if(t>=0) {
        s=get_reg(i_regs->regmap,rs1[i]);
        sr=get_reg(i_regs->regmap,SR);
        temp=get_reg(i_regs->regmap,-1);
        assert(s>=0);
        //assert(s2==t);
        if(opcode2[i]==8) emit_sub(t,s,t);
        if(opcode2[i]==10) emit_subc(s,t,sr);
        //if(opcode2[i]==11) emit_subv(s,sr,temp);
        assert(opcode2[i]!=11);
        if(opcode2[i]==12) emit_add(s,t,t);
        if(opcode2[i]==14) emit_addc(s,t,sr);
        //if(opcode2[i]==15) emit_addv(s,sr,temp);
        assert(opcode2[i]!=15);
      }
    }
  }
  if(opcode[i]==4) { // DT/CMPPZ/CMPPL
    signed char s,t,sr,temp;
    s=get_reg(i_regs->regmap,rs1[i]);
    sr=get_reg(i_regs->regmap,SR);
    assert(s>=0);
    assert(sr>=0);
    if(opcode2[i]==0) {
      t=get_reg(i_regs->regmap,rt1[i]);
      assert(t>=0); // FIXME - Liveness analysis
      assert(s==t);
      emit_dt(s,sr);
    }
    else if(opcode2[i]==1) emit_cmppz(s,sr);
    else if(opcode2[i]==5) 
    {
      temp=get_reg(i_regs->regmap,-1);
      emit_cmppl(s,sr,temp);
    }
  }
  if(opcode[i]==6) { // NOT/SWAP/NEG
    int s=get_reg(i_regs->regmap,rs1[i]);
    int t=get_reg(i_regs->regmap,rt1[i]);
    if(s<0) {
      // FIXME: Preload?
      emit_loadreg(rs1[i],t);
      s=t;
    }
    if(t>=0) {
      if(opcode2[i]==7) emit_not(s,t);
      if(opcode2[i]==8) emit_swapb(s,t);
      if(opcode2[i]==9) emit_rorimm(s,16,t);
      if(opcode2[i]==11) emit_neg(s,t);
    }
    if(opcode2[i]==10) { // NEGC
      int sr=get_reg(i_regs->regmap,SR);
      if(i_regs->u&(1LL<<rt1[i])) t=-1;
      assert(sr>=0);
      emit_negc(s,t,sr);
    }
  }
}