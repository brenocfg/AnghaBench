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
typedef  int s16 ;

/* Variables and functions */
#define  ALU 144 
#define  CJUMP 143 
#define  COMPLEX 142 
#define  EXT 141 
#define  FLAGS 140 
#define  IMM8 139 
#define  LOAD 138 
 size_t MACH ; 
 size_t MACL ; 
#define  MOV 137 
#define  MULTDIV 136 
#define  PCREL 135 
 int /*<<< orphan*/  POSTINC ; 
 int /*<<< orphan*/  PREDEC ; 
#define  RJUMP 134 
#define  RMW 133 
#define  SHIFTIMM 132 
#define  SJUMP 131 
#define  STORE 130 
#define  SYSTEM 129 
#define  UJUMP 128 
 int /*<<< orphan*/ * addrmode ; 
 int /*<<< orphan*/  assert (int) ; 
 int* imm ; 
 int* itype ; 
 int* opcode ; 
 int* opcode2 ; 
 int* rs1 ; 
 size_t* rt1 ; 
 size_t* rt2 ; 
 int /*<<< orphan*/  sh2_clear_const (int*,int*,size_t) ; 
 int /*<<< orphan*/  sh2_set_const (int*,int*,size_t,int) ; 
 int slen ; 
 int* source ; 
 int start ; 

do_consts(int i,u32 *isconst,u32 *constmap)
{
  switch(itype[i]) {
    case LOAD:
      sh2_clear_const(isconst,constmap,rt1[i]);
      if(addrmode[i]==POSTINC) {
        int size=(opcode[i]==4)?2:(opcode2[i]&3);
        constmap[rt2[i]]+=1<<size;
      }
      break;
    case STORE:
      if(addrmode[i]==PREDEC) {
        int size=(opcode[i]==4)?2:(opcode2[i]&3);
        constmap[rt1[i]]-=1<<size;
      }
      break;
    case RMW:
      break;
    case PCREL:
      if(opcode[i]==12) sh2_set_const(isconst,constmap,rt1[i],((start+i*2+4)&~3)+imm[i]); // MOVA
      else { // PC-relative load (constant pool)
        u32 addr=((start+i*2+4)&~3)+imm[i];
        if((u32)((addr-start)>>1)<slen) {
          int value;
          if(opcode[i]==9) value=(s16)source[((start+i*2+4)+imm[i]-start)>>1]; // MOV.W
          else value=(source[(((start+i*2+4)&~3)+imm[i]-start)>>1]<<16)+source[(((start+i*2+4)&~3)+imm[i]+2-start)>>1]; // MOV.L
          sh2_set_const(isconst,constmap,rt1[i],value);
        }
        else sh2_clear_const(isconst,constmap,rt1[i]);
      }
      break;
    case MOV:
      if(((*isconst)>>rs1[i])&1) {
        int v=constmap[rs1[i]];
        sh2_set_const(isconst,constmap,rt1[i],v);
      }
      else sh2_clear_const(isconst,constmap,rt1[i]);
      break;
    case IMM8:
      if(opcode[i]==0x7) { // ADD
        if(((*isconst)>>rs1[i])&1) {
          int v=constmap[rs1[i]];
          sh2_set_const(isconst,constmap,rt1[i],v+imm[i]);
        }
        else sh2_clear_const(isconst,constmap,rt1[i]);
      }
      else if(opcode[i]==0x8) { // CMP/EQ
      }
      else if(opcode[i]==12) {
        if(opcode2[i]==8) { // TST
        }else
        // AND/XOR/OR
        if(((*isconst)>>rs1[i])&1) {
          int v=constmap[rs1[i]];
          if(opcode2[i]==0x09) sh2_set_const(isconst,constmap,rt1[i],v&imm[i]);
          if(opcode2[i]==0x0a) sh2_set_const(isconst,constmap,rt1[i],v^imm[i]);
          if(opcode2[i]==0x0b) sh2_set_const(isconst,constmap,rt1[i],v|imm[i]);
        }
        else sh2_clear_const(isconst,constmap,rt1[i]);
      }
      else { // opcode[i]==0xE
        assert(opcode[i]==0xE);
        sh2_set_const(isconst,constmap,rt1[i],imm[i]); // MOV
      }
      break;
    case FLAGS:
      if(opcode2[i]==9) { // MOVT
        sh2_clear_const(isconst,constmap,rt1[i]);
      }
      break;
    case ALU:
      sh2_clear_const(isconst,constmap,rt1[i]);
      break;
    case EXT:
      sh2_clear_const(isconst,constmap,rt1[i]);
      break;
    case MULTDIV:
      if(opcode[i]==0) {
        if(opcode2[i]==7) // MUL.L
        {
          sh2_clear_const(isconst,constmap,MACL);
        }
        if(opcode2[i]==8) // CLRMAC
        {
          sh2_clear_const(isconst,constmap,MACH);
          sh2_clear_const(isconst,constmap,MACL);
        }
        if(opcode2[i]==9) // DIV0U
        {
        }
      }
      if(opcode[i]==2) {
        if(opcode2[i]==7) // DIV0S
        {
        }
        if(opcode2[i]==14||opcode2[i]==15) // MULU.W / MULS.W
        {
          sh2_clear_const(isconst,constmap,MACL);
        }
      }
      if(opcode[i]==3) {
        // DMULU.L / DMULS.L
        sh2_clear_const(isconst,constmap,MACH);
        sh2_clear_const(isconst,constmap,MACL);
      }
      break;
    case SHIFTIMM:
      sh2_clear_const(isconst,constmap,rt1[i]);
      break;
    case UJUMP:
    case RJUMP:
    case SJUMP:
    case CJUMP:
      break;
    case SYSTEM:
      *isconst=0;
      break;
    case COMPLEX:
      *isconst=0;
      break;
  }
}