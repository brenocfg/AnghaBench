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
 scalar_t__ SR ; 
 long long TBIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_rotclsr (char,char) ; 
 int /*<<< orphan*/  emit_rotcrsr (char,char) ; 
 int /*<<< orphan*/  emit_rotl (char) ; 
 int /*<<< orphan*/  emit_rotlsr (char,char) ; 
 int /*<<< orphan*/  emit_rotr (char) ; 
 int /*<<< orphan*/  emit_rotrsr (char,char) ; 
 int /*<<< orphan*/  emit_sarimm (char,int,char) ; 
 int /*<<< orphan*/  emit_sarsr (char,char) ; 
 int /*<<< orphan*/  emit_shlimm (char,int,char) ; 
 int /*<<< orphan*/  emit_shlsr (char,char) ; 
 int /*<<< orphan*/  emit_shrdimm (char,char,int,char) ; 
 int /*<<< orphan*/  emit_shrimm (char,int,char) ; 
 int /*<<< orphan*/  emit_shrsr (char,char) ; 
 char get_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int* opcode ; 
 int* opcode2 ; 
 int* opcode3 ; 
 scalar_t__* rs1 ; 
 scalar_t__* rs2 ; 
 scalar_t__* rt1 ; 

void shiftimm_assemble(int i,struct regstat *i_regs)
{
  if(opcode[i]==4) // SHL/SHR
  {
    if(opcode2[i]<8) {
      signed char s,t,sr;
      s=get_reg(i_regs->regmap,rs1[i]);
      t=get_reg(i_regs->regmap,rt1[i]);
      sr=get_reg(i_regs->regmap,SR);
      assert(s==t);
      if(opcode2[i]==0) // SHLL/SHAL
      {
        if(i_regs->u&(1LL<<TBIT)) emit_shlimm(s,1,s);
        else emit_shlsr(s,sr); // Is there any difference between SHLL and SHAL?
      }
      else if(opcode2[i]==1) // SHLR/SHAR
      {
        if(i_regs->u&(1LL<<TBIT)) {
          // Skip T bit if unneeded
          if(opcode3[i]==0) emit_shrimm(s,1,s);
          if(opcode3[i]==2) emit_sarimm(s,1,s);
        }else{
          // Set T bit
          if(opcode3[i]==0) emit_shrsr(s,sr);
          if(opcode3[i]==2) emit_sarsr(s,sr);
        }
      }
      else if(opcode2[i]==4) {// ROTL/ROTCL
        if(opcode3[i]==0) {
          if(i_regs->u&(1LL<<TBIT)) {
            emit_rotl(s); // Skip T bit if unneeded
          }else{
            emit_rotlsr(s,sr);
          }
        }
        if(opcode3[i]==2) emit_rotclsr(s,sr);
      }
      else {
        assert(opcode2[i]==5); // ROTR/ROTCR
        if(opcode3[i]==0) {
          if(i_regs->u&(1LL<<TBIT)) {
            emit_rotr(s); // Skip T bit if unneeded
          }else{
            emit_rotrsr(s,sr);
          }
        }
        if(opcode3[i]==2) emit_rotcrsr(s,sr);
      }
    }else{
      signed char s,t;
      s=get_reg(i_regs->regmap,rs1[i]);
      t=get_reg(i_regs->regmap,rt1[i]);
      //assert(t>=0);
      if(t>=0){
        if(opcode2[i]==8) // SHLL
        {
          if(opcode3[i]==0) emit_shlimm(s,2,t);
          if(opcode3[i]==1) emit_shlimm(s,8,t);
          if(opcode3[i]==2) emit_shlimm(s,16,t);
        }
        if(opcode2[i]==9) // SHLR
        {
          if(opcode3[i]==0) emit_shrimm(s,2,t);
          if(opcode3[i]==1) emit_shrimm(s,8,t);
          if(opcode3[i]==2) emit_shrimm(s,16,t);
        }
      }
    }
  }
  else if(opcode[i]==2) // XTRCT
  {
    signed char s,t,sr;
    s=get_reg(i_regs->regmap,rs1[i]);
    t=get_reg(i_regs->regmap,rt1[i]);
    assert(rs2[i]==rt1[i]);
    emit_shrdimm(t,s,16,t);
  }
}