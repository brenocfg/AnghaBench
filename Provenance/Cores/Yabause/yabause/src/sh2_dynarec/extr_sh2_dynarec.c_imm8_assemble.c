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
struct regstat {char isdoingcp; int* regmap_entry; char wasdoingcp; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SR ; 
 int /*<<< orphan*/  assert (int) ; 
 int** cpmap ; 
 int /*<<< orphan*/  emit_addimm (char,int,char) ; 
 int /*<<< orphan*/  emit_andimm (char,int,char) ; 
 int /*<<< orphan*/  emit_cmpeqimm (char,int,char,char) ; 
 int /*<<< orphan*/  emit_loadreg (int,char) ; 
 int /*<<< orphan*/  emit_movimm (int,char) ; 
 int /*<<< orphan*/  emit_orimm (char,int,char) ; 
 int /*<<< orphan*/  emit_sh2tstimm (char,int,char,char) ; 
 int /*<<< orphan*/  emit_xorimm (char,int,char) ; 
 char get_reg (int /*<<< orphan*/ ,int) ; 
 int* imm ; 
 int* opcode ; 
 int* opcode2 ; 
 int* rs1 ; 
 int* rt1 ; 

void imm8_assemble(int i,struct regstat *i_regs)
{
  if(opcode[i]==0x7) { // ADD
    signed char s,t;
    t=get_reg(i_regs->regmap,rt1[i]);
    s=get_reg(i_regs->regmap,rs1[i]);
    //assert(t>=0);
    assert(s>=0);
    if(t>=0) {
      if(!((i_regs->isdoingcp>>t)&1)) {
        if(s<0) {
          if(i_regs->regmap_entry[t]!=rs1[i]) emit_loadreg(rs1[i],t);
          emit_addimm(t,imm[i],t);
        }else{
          if(!((i_regs->wasdoingcp>>s)&1))
            emit_addimm(s,imm[i],t);
          else
            emit_movimm(cpmap[i][s]+imm[i],t);
        }
      }
    }
  }
  else if(opcode[i]==0x8) { // CMP/EQ
    signed char s,sr,temp;
    s=get_reg(i_regs->regmap,rs1[i]);
    sr=get_reg(i_regs->regmap,SR);
    temp=get_reg(i_regs->regmap,-1);
    assert(s>=0);
    assert(sr>=0); // Liveness analysis?
    assert(temp>=0);
    emit_cmpeqimm(s,imm[i],sr,temp);
  }
  else if(opcode[i]==12) {
    if(opcode2[i]==8) { // TST
      signed char s,sr,temp;
      s=get_reg(i_regs->regmap,rs1[i]);
      sr=get_reg(i_regs->regmap,SR);
      temp=get_reg(i_regs->regmap,-1);
      assert(s>=0);
      assert(sr>=0); // Liveness analysis?
      assert(temp>=0);
      emit_sh2tstimm(s,imm[i],sr,temp);
    }else{
      signed char s,t;
      t=get_reg(i_regs->regmap,rt1[i]);
      s=get_reg(i_regs->regmap,rs1[i]);
      if(t>=0 && !((i_regs->isdoingcp>>t)&1)) {
        if(opcode2[i]==9) //AND
        {
          if(s<0) {
            if(i_regs->regmap_entry[t]!=rs1[i]) emit_loadreg(rs1[i],t);
            emit_andimm(t,imm[i],t);
          }else{
            if(!((i_regs->wasdoingcp>>s)&1))
              emit_andimm(s,imm[i],t);
            else
              emit_movimm(cpmap[i][s]&imm[i],t);
          }
        }
        else
        if(opcode2[i]==10) //XOR
        {
          if(s<0) {
            if(i_regs->regmap_entry[t]!=rs1[i]) emit_loadreg(rs1[i],t);
            emit_xorimm(t,imm[i],t);
          }else{
            if(!((i_regs->wasdoingcp>>s)&1))
              emit_xorimm(s,imm[i],t);
            else
              emit_movimm(cpmap[i][s]^imm[i],t);
          }
        }
        else
        if(opcode2[i]==11) //OR
        {
          if(s<0) {
            if(i_regs->regmap_entry[t]!=rs1[i]) emit_loadreg(rs1[i],t);
            emit_orimm(t,imm[i],t);
          }else{
            if(!((i_regs->wasdoingcp>>s)&1))
              emit_orimm(s,imm[i],t);
            else
              emit_movimm(cpmap[i][s]|imm[i],t);
          }
        }
      }
    }
  }
  else { // opcode[i]==0xE
    signed char t;
    assert(opcode[i]==0xE);
    t=get_reg(i_regs->regmap,rt1[i]);
    //assert(t>=0);
    if(t>=0) {
      if(!((i_regs->isdoingcp>>t)&1))
        emit_movimm(imm[i]<<16,t);
    }
  }
}