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
typedef  long long u64 ;
struct regstat {char* regmap; } ;
struct TYPE_4__ {scalar_t__* regmap; int /*<<< orphan*/  dirty; } ;
struct TYPE_3__ {scalar_t__* regmap; long long u; int /*<<< orphan*/  dirty; int /*<<< orphan*/  regmap_entry; } ;

/* Variables and functions */
 int CCREG ; 
 int CLOCK_DIVIDER ; 
 int EXCLUDE_REG ; 
 int HOST_CCREG ; 
 int HOST_REGS ; 
 int HOST_TEMPREG ; 
 long long PR ; 
 char PTEMP ; 
 int /*<<< orphan*/  TAKEN ; 
 int /*<<< orphan*/  add_to_linker (int,int,scalar_t__) ; 
 int /*<<< orphan*/  address_generation (int,struct regstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assem_debug (char*,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* ba ; 
 TYPE_2__* branch_regs ; 
 int* ccadj ; 
 int* cycles ; 
 int /*<<< orphan*/  do_cc (int,scalar_t__*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_miniht_insert (unsigned int,int,int) ; 
 int /*<<< orphan*/  ds_assemble (int,struct regstat*) ; 
 int /*<<< orphan*/  ds_assemble_entry (int) ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movimm (unsigned int,int) ; 
 int /*<<< orphan*/  emit_prefetch (scalar_t__) ; 
 int /*<<< orphan*/  emit_prefetchreg (int) ; 
 int get_reg (scalar_t__*,int) ; 
 scalar_t__* hash_table ; 
 scalar_t__ internal_branch (int) ; 
 scalar_t__* is_ds ; 
 int /*<<< orphan*/  load_regs (scalar_t__*,scalar_t__*,int,int,int) ; 
 int /*<<< orphan*/  load_regs_bt (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ out ; 
 TYPE_1__* regs ; 
 long long* rs1 ; 
 long long* rs2 ; 
 long long* rs3 ; 
 long long* rt1 ; 
 long long* rt2 ; 
 int start ; 
 int /*<<< orphan*/  store_regs_bt (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_invalidate (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,long long) ; 

void ujump_assemble(int i,struct regstat *i_regs)
{
  u64 bc_unneeded;
  int cc,adj;
  signed char *i_regmap=i_regs->regmap;
  if(i==(ba[i]-start)>>1) assem_debug("idle loop\n");
  address_generation(i+1,i_regs,regs[i].regmap_entry);
  #ifdef REG_PREFETCH
  int temp=get_reg(branch_regs[i].regmap,PTEMP);
  if(rt1[i]==PR&&temp>=0) 
  {
    int return_address=start+i*2+4;
    if(get_reg(branch_regs[i].regmap,PR)>0) 
    if(i_regmap[temp]==PTEMP) emit_movimm((int)hash_table[((return_address>>16)^return_address)&0xFFFF],temp);
  }
  #endif
  if(rt1[i]==PR) {
    if(rt1[i+1]==PR||rt2[i+1]==PR) {
      // Delay slot abuse, set PR before executing delay slot
      int rt;
      unsigned int return_address;
      rt=get_reg(regs[i].regmap,PR);
      return_address=start+i*2+4;
      assert(rt>=0);
      if(rt>=0) {
        #ifdef REG_PREFETCH
        if(temp>=0) 
        {
          if(i_regmap[temp]!=PTEMP) emit_movimm((int)hash_table[((return_address>>16)^return_address)&0xFFFF],temp);
        }
        #endif
        emit_movimm(return_address,rt); // PC into link register
      }
    }
  }
  ds_assemble(i+1,i_regs);
  bc_unneeded=regs[i].u;
  bc_unneeded|=1LL<<rt1[i];
  wb_invalidate(regs[i].regmap,branch_regs[i].regmap,regs[i].dirty,
                bc_unneeded);
  load_regs(regs[i].regmap,branch_regs[i].regmap,CCREG,CCREG,CCREG);
  if(rt1[i]==PR) {
    int rt;
    unsigned int return_address;
    assert(rs1[i+1]!=PR);
    assert(rs2[i+1]!=PR);
    assert(rs3[i+1]!=PR);
    rt=get_reg(branch_regs[i].regmap,PR);
    assem_debug("branch(%d): eax=%d ecx=%d edx=%d ebx=%d ebp=%d esi=%d edi=%d\n",i,branch_regs[i].regmap[0],branch_regs[i].regmap[1],branch_regs[i].regmap[2],branch_regs[i].regmap[3],branch_regs[i].regmap[5],branch_regs[i].regmap[6],branch_regs[i].regmap[7]);
    //assert(rt>=0);
    return_address=start+i*2+4;
    if(rt>=0&&rt1[i+1]!=PR&&rt2[i+1]!=PR) {
      #ifdef USE_MINI_HT
      if(internal_branch(return_address)) {
        int temp=rt+1;
        if(temp==EXCLUDE_REG||temp>=HOST_REGS||
           branch_regs[i].regmap[temp]>=0)
        {
          temp=get_reg(branch_regs[i].regmap,-1);
        }
        #ifdef HOST_TEMPREG
        if(temp<0) temp=HOST_TEMPREG;
        #endif
        if(temp>=0) do_miniht_insert(return_address,rt,temp);
        else emit_movimm(return_address,rt);
      }
      else
      #endif
      {
        #ifdef REG_PREFETCH
        if(temp>=0) 
        {
          if(i_regmap[temp]!=PTEMP) emit_movimm((int)hash_table[((return_address>>16)^return_address)&0xFFFF],temp);
        }
        #endif
        emit_movimm(return_address,rt); // PC into link register
        #ifdef IMM_PREFETCH
        emit_prefetch(hash_table[((return_address>>16)^return_address)&0xFFFF]);
        #endif
      }
    }
  }
  cc=get_reg(branch_regs[i].regmap,CCREG);
  assert(cc==HOST_CCREG);
  store_regs_bt(branch_regs[i].regmap,branch_regs[i].dirty,ba[i]);
  #ifdef REG_PREFETCH
  if(rt1[i]==PR&&temp>=0) emit_prefetchreg(temp);
  #endif
  do_cc(i,branch_regs[i].regmap,&adj,ba[i],TAKEN,0);
  if(adj) emit_addimm(cc,CLOCK_DIVIDER*(ccadj[i]+cycles[i]+cycles[i+1]-adj),cc);
  load_regs_bt(branch_regs[i].regmap,branch_regs[i].dirty,ba[i]);
  if(internal_branch(ba[i]))
    assem_debug("branch: internal\n");
  else
    assem_debug("branch: external\n");
  if(internal_branch(ba[i])&&is_ds[(ba[i]-start)>>1]) {
    ds_assemble_entry(i);
  }
  else {
    add_to_linker((int)out,ba[i],internal_branch(ba[i]));
    emit_jmp(0);
  }
}