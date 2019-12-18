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
struct regstat {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regmap_entry; } ;
typedef  int /*<<< orphan*/  pointer ;

/* Variables and functions */
 int EBP ; 
 int EDI ; 
 int /*<<< orphan*/  MACH ; 
 int /*<<< orphan*/  MACL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ div1 ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  load_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ macl ; 
 scalar_t__ macw ; 
 int* opcode ; 
 int* opcode2 ; 
 scalar_t__* rs1 ; 
 scalar_t__* rs2 ; 

void complex_assemble(int i,struct regstat *i_regs)
{
  if(opcode[i]==3&&opcode2[i]==4) { // DIV1
    emit_call((pointer)div1);
  }
  if(opcode[i]==0&&opcode2[i]==15) { // MAC.L
    load_regs(i_regs->regmap_entry,i_regs->regmap,MACL,MACH,MACH);
    // If both registers are the same, the register is incremented twice.
    // Pre-increment one of the function arguments.
    #if defined(__i386__) || defined(__x86_64__)
    if(rs1[i]==rs2[i]) {emit_mov(EDI,EBP);emit_addimm(EDI,4,EDI);}
    #else
    #if defined(__arm__)
    if(rs1[i]==rs2[i]) {emit_mov(6,5);emit_addimm(6,4,6);}
    #else
    // FIXME
    assert(0);
    #endif
    #endif
/* DEBUG
  //if(i_regmap[HOST_CCREG]!=CCREG) {
    emit_loadreg(CCREG,ECX);
    emit_addimm(ECX,CLOCK_DIVIDER*(ccadj[i]),ECX);
    output_byte(0x03);
    output_modrm(1,4,ECX);
    output_sib(0,4,4);
    output_byte(4);
    emit_writeword(ECX,slave?(int)&SSH2->cycles:(int)&MSH2->cycles);
//  }*/
    emit_call((pointer)macl);
  }
  if(opcode[i]==4&&opcode2[i]==15) { // MAC.W
    load_regs(i_regs->regmap_entry,i_regs->regmap,MACL,MACH,MACH);
    // If both registers are the same, the register is incremented twice.
    // Pre-increment one of the function arguments.
    #if defined(__i386__) || defined(__x86_64__)
    if(rs1[i]==rs2[i]) {emit_mov(EDI,EBP);emit_addimm(EDI,2,EDI);}
    #else
    #if defined(__arm__)
    if(rs1[i]==rs2[i]) {emit_mov(6,5);emit_addimm(6,2,6);}
    #else
    // FIXME
    assert(0);
    #endif
    #endif
/* DEBUG
  //if(i_regmap[HOST_CCREG]!=CCREG) {
    emit_loadreg(CCREG,ECX);
    emit_addimm(ECX,CLOCK_DIVIDER*(ccadj[i]),ECX);
    output_byte(0x03);
    output_modrm(1,4,ECX);
    output_sib(0,4,4);
    output_byte(4);
    emit_writeword(ECX,slave?(int)&SSH2->cycles:(int)&MSH2->cycles);
//  }*/
    emit_call((pointer)macw);
  }
}