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
struct regstat {int dummy; } ;

/* Variables and functions */
#define  ALU 145 
#define  CJUMP 144 
#define  COMPLEX 143 
#define  EXT 142 
#define  FLAGS 141 
#define  IMM8 140 
#define  LOAD 139 
#define  MOV 138 
#define  MULTDIV 137 
#define  PCREL 136 
#define  RJUMP 135 
#define  RMW 134 
#define  SHIFTIMM 133 
#define  SJUMP 132 
#define  STORE 131 
#define  SYSCALL 130 
#define  SYSTEM 129 
#define  UJUMP 128 
 int /*<<< orphan*/  alu_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  complex_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  ext_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  flags_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  imm8_assemble (int,struct regstat*) ; 
 int is_delayslot ; 
 int* itype ; 
 int /*<<< orphan*/  load_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  mov_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  multdiv_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  pcrel_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rmw_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  shiftimm_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  store_assemble (int,struct regstat*) ; 

void ds_assemble(int i,struct regstat *i_regs)
{
  is_delayslot=1;
  switch(itype[i]) {
    case ALU:
      alu_assemble(i,i_regs);break;
    case IMM8:
      imm8_assemble(i,i_regs);break;
    case SHIFTIMM:
      shiftimm_assemble(i,i_regs);break;
    case LOAD:
      load_assemble(i,i_regs);break;
    case STORE:
      store_assemble(i,i_regs);break;
    case RMW:
      rmw_assemble(i,i_regs);break;
    case PCREL:
      pcrel_assemble(i,i_regs);break;
    case MULTDIV:
      multdiv_assemble(i,i_regs);break;
    case MOV:
      mov_assemble(i,i_regs);break;
    case EXT:
      ext_assemble(i,i_regs);break;
    case FLAGS:
      flags_assemble(i,i_regs);break;
    case COMPLEX:
      complex_assemble(i,i_regs);break;
    case SYSTEM:
    case SYSCALL:
    case UJUMP:
    case RJUMP:
    case CJUMP:
    case SJUMP:
      printf("Jump in the delay slot.  This is probably a bug.\n");
  }
  is_delayslot=0;
}