#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pointer ;
struct TYPE_15__ {scalar_t__* regmap_entry; scalar_t__* regmap; int /*<<< orphan*/  dirty; int /*<<< orphan*/  wasdirty; } ;

/* Variables and functions */
#define  ALU 145 
 scalar_t__ CCREG ; 
#define  CJUMP 144 
#define  COMPLEX 143 
#define  EXT 142 
#define  FLAGS 141 
 size_t HOST_CCREG ; 
#define  IMM8 140 
#define  LOAD 139 
 int /*<<< orphan*/  MMREG ; 
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
 int /*<<< orphan*/  add_to_linker (int,int,scalar_t__) ; 
 int /*<<< orphan*/  address_generation (int,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  alu_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  assem_debug (char*,...) ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int* ba ; 
 int /*<<< orphan*/  complex_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  flags_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  imm8_assemble (int,TYPE_1__*) ; 
 scalar_t__* instr_addr ; 
 scalar_t__ internal_branch (int) ; 
 scalar_t__ is_delayslot ; 
 int* itype ; 
 int /*<<< orphan*/  load_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  load_regs (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_regs_bt (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mov_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  multdiv_assemble (int,TYPE_1__*) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  pcrel_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* regs ; 
 int /*<<< orphan*/  rmw_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/ * rs1 ; 
 int /*<<< orphan*/ * rs2 ; 
 int /*<<< orphan*/ * rs3 ; 
 int /*<<< orphan*/  shiftimm_assemble (int,TYPE_1__*) ; 
 int start ; 
 int /*<<< orphan*/  store_assemble (int,TYPE_1__*) ; 
 int /*<<< orphan*/  store_regs_bt (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_register (scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

void ds_assemble_entry(int i)
{
  int t=(ba[i]-start)>>1;
  if(!instr_addr[t]) instr_addr[t]=(pointer)out;
  assem_debug("Assemble delay slot at %x\n",ba[i]);
  assem_debug("<->\n");
  if(regs[t].regmap_entry[HOST_CCREG]==CCREG&&regs[t].regmap[HOST_CCREG]!=CCREG)
    wb_register(CCREG,regs[t].regmap_entry,regs[t].wasdirty);
  load_regs(regs[t].regmap_entry,regs[t].regmap,rs1[t],rs2[t],rs3[t]);
  address_generation(t,&regs[t],regs[t].regmap_entry);
  if(itype[t]==LOAD||itype[t]==STORE)
    load_regs(regs[t].regmap_entry,regs[t].regmap,MMREG,MMREG,MMREG);
  is_delayslot=0;
  switch(itype[t]) {
    case ALU:
      alu_assemble(t,&regs[t]);break;
    case IMM8:
      imm8_assemble(t,&regs[t]);break;
    case SHIFTIMM:
      shiftimm_assemble(t,&regs[t]);break;
    case LOAD:
      load_assemble(t,&regs[t]);break;
    case STORE:
      store_assemble(t,&regs[t]);break;
    case RMW:
      rmw_assemble(t,&regs[t]);break;
    case PCREL:
      pcrel_assemble(t,&regs[t]);break;
    case MULTDIV:
      multdiv_assemble(t,&regs[t]);break;
    case MOV:
      mov_assemble(t,&regs[t]);break;
    case EXT:
      ext_assemble(i,&regs[t]);break;
    case FLAGS:
      flags_assemble(i,&regs[t]);break;
    case COMPLEX:
      complex_assemble(i,&regs[t]);break;
    case SYSTEM:
    case SYSCALL:
    case UJUMP:
    case RJUMP:
    case CJUMP:
    case SJUMP:
      printf("Jump in the delay slot.  This is probably a bug.\n");
  }
  store_regs_bt(regs[t].regmap,regs[t].dirty,ba[i]+2);
  load_regs_bt(regs[t].regmap,regs[t].dirty,ba[i]+2);
  if(internal_branch(ba[i]+2))
    assem_debug("branch: internal\n");
  else
    assem_debug("branch: external\n");
  assert(internal_branch(ba[i]+2));
  add_to_linker((int)out,ba[i]+2,internal_branch(ba[i]+2));
  emit_jmp(0);
}