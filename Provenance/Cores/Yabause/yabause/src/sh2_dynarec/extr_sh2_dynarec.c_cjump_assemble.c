#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regstat {char* regmap; } ;
typedef  scalar_t__ pointer ;
struct TYPE_4__ {int /*<<< orphan*/  dirty; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  dirty; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCREG ; 
 int /*<<< orphan*/  CC_STUB ; 
 int CLOCK_DIVIDER ; 
 int HOST_CCREG ; 
 int /*<<< orphan*/  NODS ; 
 int /*<<< orphan*/  NOTTAKEN ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  TAKEN ; 
 int /*<<< orphan*/  add_stub (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_linker (int,int,int) ; 
 int /*<<< orphan*/  assem_debug (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* ba ; 
 TYPE_2__* branch_regs ; 
 int* ccadj ; 
 int /*<<< orphan*/  do_cc (int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ds_assemble_entry (int) ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_addimm_and_set_flags (int,int) ; 
 int /*<<< orphan*/  emit_addnop (int) ; 
 int /*<<< orphan*/  emit_jeq (int) ; 
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jne (int) ; 
 int /*<<< orphan*/  emit_jns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_testimm (int,int) ; 
 int get_reg (char*,int /*<<< orphan*/ ) ; 
 int internal_branch (int) ; 
 scalar_t__* is_ds ; 
 int /*<<< orphan*/  load_regs_bt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int match_bt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* opcode2 ; 
 scalar_t__ out ; 
 TYPE_1__* regs ; 
 int /*<<< orphan*/  set_jump_target (scalar_t__,scalar_t__) ; 
 scalar_t__* source ; 
 int start ; 
 int /*<<< orphan*/  store_regs_bt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void cjump_assemble(int i,struct regstat *i_regs)
{
  signed char *i_regmap=i_regs->regmap;
  int cc;
  int match;
  int sr;
  int unconditional=0,nop=0;
  int adj;
  int invert=0;
  int internal;
  match=match_bt(regs[i].regmap,regs[i].dirty,ba[i]);
  assem_debug("match=%d\n",match);
  internal=internal_branch(ba[i]);
  if(i==(ba[i]-start)>>1) assem_debug("idle loop\n");
  if(!match) invert=1;
  #ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
  if(i>(ba[i]-start)>>1) invert=1;
  #endif
  sr=get_reg(i_regmap,SR);
  assert(sr>=0);
  cc=get_reg(i_regmap,CCREG);
  assert(cc==HOST_CCREG);
  do_cc(i,regs[i].regmap,&adj,start+i*2,NODS,invert);
  if(unconditional) 
    store_regs_bt(branch_regs[i].regmap,branch_regs[i].dirty,ba[i]);
  if(unconditional) {
    do_cc(i,branch_regs[i].regmap,&adj,ba[i],TAKEN,0);
    if(i!=(ba[i]-start)>>1 || source[i+1]!=0) {
      if(adj) emit_addimm(cc,CLOCK_DIVIDER*(ccadj[i]+2-adj),cc);
      load_regs_bt(branch_regs[i].regmap,branch_regs[i].dirty,ba[i]);
      if(internal)
        assem_debug("branch: internal\n");
      else
        assem_debug("branch: external\n");
      if(internal&&is_ds[(ba[i]-start)>>1]) {
        ds_assemble_entry(i);
      }
      else {
        add_to_linker((int)out,ba[i],internal);
        emit_jmp(0);
      }
      #ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
      if(((u32)out)&7) emit_addnop(0);
      #endif
    }
  }
  else if(nop) {
    int jaddr;
    emit_addimm_and_set_flags(CLOCK_DIVIDER*(ccadj[i]+2),cc);
    jaddr=(int)out;
    emit_jns(0);
    add_stub(CC_STUB,jaddr,(int)out,0,i,start+i*2+4,NOTTAKEN,0);
  }
  else {
    pointer taken=0,nottaken=0,nottaken1=0;
    //do_cc(i,regs[i].regmap,&adj,-1,0,invert);
    if(adj&&!invert) emit_addimm(cc,CLOCK_DIVIDER*(ccadj[i]-adj),cc);
    
    //printf("branch(%d): eax=%d ecx=%d edx=%d ebx=%d ebp=%d esi=%d edi=%d\n",i,branch_regs[i].regmap[0],branch_regs[i].regmap[1],branch_regs[i].regmap[2],branch_regs[i].regmap[3],branch_regs[i].regmap[5],branch_regs[i].regmap[6],branch_regs[i].regmap[7]);
    emit_testimm(sr,1);
    if(opcode2[i]==9) // BT
    {
      if(invert){
        nottaken=(pointer)out;
        emit_jeq(1);
      }else{
        add_to_linker((int)out,ba[i],internal);
        emit_jne(0);
      }
    }
    if(opcode2[i]==11) // BF
    {
      if(invert){
        nottaken=(pointer)out;
        emit_jne(1);
      }else{
        add_to_linker((int)out,ba[i],internal);
        emit_jeq(0);
      }
    }
    if(invert) {
      if(taken) set_jump_target(taken,(pointer)out);
      #ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
      if(match&&(!internal||!is_ds[(ba[i]-start)>>1])) {
        if(adj) {
          emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
          add_to_linker((int)out,ba[i],internal);
        }else{
          emit_addnop(13);
          add_to_linker((int)out,ba[i],internal*2);
        }
        emit_jmp(0);
      }else
      #endif
      {
        if(adj) emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
        store_regs_bt(regs[i].regmap,regs[i].dirty,ba[i]);
        load_regs_bt(regs[i].regmap,regs[i].dirty,ba[i]);
        if(internal)
          assem_debug("branch: internal\n");
        else
          assem_debug("branch: external\n");
        if(internal&&is_ds[(ba[i]-start)>>1]) {
          ds_assemble_entry(i);
        }
        else {
          add_to_linker((int)out,ba[i],internal);
          emit_jmp(0);
        }
      }
      set_jump_target(nottaken,(pointer)out);
    }

    //if(nottaken1) set_jump_target(nottaken1,(int)out);
    if(adj&&!invert) emit_addimm(cc,CLOCK_DIVIDER*adj,cc);
  } // (!unconditional)
}