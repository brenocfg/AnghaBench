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
struct regstat {scalar_t__* regmap; int wasdoingcp; int isconst; int* constmap; long long u; } ;

/* Variables and functions */
 int AGEN1 ; 
 scalar_t__ DUALIND ; 
 unsigned int HOST_REGS ; 
 int MMREG ; 
 int MOREG ; 
 scalar_t__ PREDEC ; 
 scalar_t__ REGIND ; 
 int STOREB_STUB ; 
 int STOREL_STUB ; 
 int STOREW_STUB ; 
 int /*<<< orphan*/  add_stub (int,int,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__* addrmode ; 
 int /*<<< orphan*/  assert (int) ; 
 int can_direct_write (int) ; 
 int /*<<< orphan*/ * ccadj ; 
 int** cpmap ; 
 int do_map_w (int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  do_map_w_branch (int,int,int,int*) ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 int /*<<< orphan*/  emit_rorimm (int,int,int) ; 
 int /*<<< orphan*/  emit_writebyte_indexed_map (int,int,int,int,int) ; 
 int /*<<< orphan*/  emit_writehword_indexed_map (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  emit_writeword_indexed_map (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  generate_map_const (int,int) ; 
 int get_alt_reg (scalar_t__*,int) ; 
 int get_reg (scalar_t__*,int) ; 
 int* imm ; 
 int /*<<< orphan*/  inline_writestub (int,int,int,scalar_t__*,int,int /*<<< orphan*/ ,int) ; 
 int* opcode ; 
 int* opcode2 ; 
 scalar_t__ out ; 
 int* rs1 ; 
 int* rs2 ; 
 int* rs3 ; 
 int* rt1 ; 

void store_assemble(int i,struct regstat *i_regs)
{
  int s,t,o,map=-1,cache=-1;
  int addr,temp;
  int offset;
  int jaddr=0,jaddr2,type;
  int memtarget,c=0,constaddr;
  int dualindex=(addrmode[i]==DUALIND);
  int size=(opcode[i]==4)?2:(opcode2[i]&3);
  int agr=AGEN1+(i&1);
  unsigned int hr;
  u32 reglist=0;
  t=get_reg(i_regs->regmap,rs1[i]);
  s=get_reg(i_regs->regmap,rs2[i]);
  o=get_reg(i_regs->regmap,rs3[i]);
  temp=get_reg(i_regs->regmap,agr);
  if(temp<0) temp=get_reg(i_regs->regmap,-1);
  offset=imm[i];
  for(hr=0;hr<HOST_REGS;hr++) {
    if(i_regs->regmap[hr]>=0) reglist|=1<<hr;
  }
  //if(i_regs->regmap[HOST_CCREG]==CCREG) reglist&=~(1<<HOST_CCREG);
  if(s>=0) {
    if(dualindex)
      c=(i_regs->wasdoingcp>>s)&(i_regs->wasdoingcp>>o)&1;
    else
      c=(i_regs->wasdoingcp>>s)&1;
    if(c) {
      if(dualindex)
        constaddr=cpmap[i][s]+cpmap[i][o];
      else
        constaddr=cpmap[i][s]+offset;
    }
    //printf("constaddr=%x offset=%x\n",constaddr,offset);
    memtarget=can_direct_write(constaddr);
  }
  if(!c) {
    if(dualindex) {
      c=(i_regs->isconst>>rs2[i])&(i_regs->isconst>>rs3[i])&1;
    } else {
      c=(i_regs->isconst>>rs2[i])&1;
    }
    if(c) {
      if(dualindex)
        constaddr=i_regs->constmap[rs2[i]]+i_regs->constmap[rs3[i]];
      else
        constaddr=i_regs->constmap[rs2[i]]+offset;
      //printf("constaddr=%x offset=%x\n",constaddr,offset);
      memtarget=can_direct_write(constaddr);
      // In this case, the constant is not already loaded into a register
      if(can_direct_write(constaddr)) {
        emit_movimm(constaddr^(!size),temp);
        map=get_reg(i_regs->regmap,MOREG);
        if(map<0) map=get_alt_reg(i_regs->regmap,-1);
        generate_map_const(constaddr,map);
      }
    }
  }
  assert(t>=0);
  assert(temp>=0);
  if(offset||dualindex||s<0||c) addr=temp;
  else addr=s;
  //printf("store_assemble: c=%d\n",c);
  if(addrmode[i]==PREDEC&&!c&&rt1[i]==rs1[i]) addr=temp; // Old value is written, so decremented address is in a temporary register
  if(addrmode[i]==REGIND&&!c&&rs1[i]==rs2[i]) {// Swapped value is written, so unswapped value must be used as the address
    emit_mov(addr,temp);addr=temp;
  }
  if(!c||memtarget)
  {
    int x=0;
    if (!c&&size==0) x=1; // MOV.B
    cache=get_reg(i_regs->regmap,MMREG);
    map=get_reg(i_regs->regmap,MOREG);
    if(map<0) map=get_alt_reg(i_regs->regmap,-1);
    assert(map>=0);
    assert(map!=temp);
    assert(map!=s);
    reglist&=~(1<<map);
    //if(x) emit_xorimm(addr,x,temp); // for debugging
    map=do_map_w(addr,temp,map,cache,x,c,constaddr);
    if (!c&&size==0) addr=temp; // MOV.B
    do_map_w_branch(map,c,constaddr,&jaddr);
    //jaddr=(int)out;emit_jmp(0); // for debugging
  }

  if (size==0) { // MOV.B
    if(!c||memtarget) {
      int x=0;
      emit_writebyte_indexed_map(t,x,temp,map,temp);
    }
    type=STOREB_STUB;
  }
  if (size==1) { // MOV.W
    if(!c||memtarget) {
      emit_writehword_indexed_map(t,0,addr,map,temp);
    }
    type=STOREW_STUB;
  }
  if (size==2) { // MOV.L
    if(!c||memtarget) {
      emit_rorimm(t,16,t);
      emit_writeword_indexed_map(t,0,addr,map,temp);
      if(!(i_regs->u&(1LL<<rs1[i]))) 
        emit_rorimm(t,16,t);
    }
    type=STOREL_STUB;
  }
  if(jaddr) {
    add_stub(type,jaddr,(int)out,i,addr,(int)i_regs,ccadj[i],reglist);
  } else if(c&&!memtarget) {
    inline_writestub(type,i,constaddr,i_regs->regmap,rs1[i],ccadj[i],reglist);
  }
  if(addrmode[i]==PREDEC) {
    assert(s>=0);
    if(!((i_regs->wasdoingcp>>s)&1)&&rt1[i]==rs1[i]) emit_addimm(s,-(1<<size),s); // Old value is written, so this "pre-decrement" is really post-decrement
  }
  //if(opcode[i]==0x2B || opcode[i]==0x3F)
  //if(opcode[i]==0x2B || opcode[i]==0x28)
  //if(opcode[i]==0x2B || opcode[i]==0x29)
  //if(opcode[i]==0x2B)
  /*if(opcode[i]==0x2B || opcode[i]==0x28 || opcode[i]==0x29 || opcode[i]==0x3F)
  {
    //emit_pusha();
    save_regs(0x100f);
        emit_readword((int)&last_count,ECX);
        #ifdef __i386__
        if(get_reg(i_regs->regmap,CCREG)<0)
          emit_loadreg(CCREG,HOST_CCREG);
        emit_add(HOST_CCREG,ECX,HOST_CCREG);
        emit_addimm(HOST_CCREG,2*ccadj[i],HOST_CCREG);
        emit_writeword(HOST_CCREG,(int)&Count);
        #endif
        #ifdef __arm__
        if(get_reg(i_regs->regmap,CCREG)<0)
          emit_loadreg(CCREG,0);
        else
          emit_mov(HOST_CCREG,0);
        emit_add(0,ECX,0);
        emit_addimm(0,2*ccadj[i],0);
        emit_writeword(0,(int)&Count);
        #endif
    emit_call((int)memdebug);
    //emit_popa();
    restore_regs(0x100f);
  }/**/
}