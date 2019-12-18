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
struct regstat {scalar_t__* regmap; int isdoingcp; } ;

/* Variables and functions */
 scalar_t__ CCREG ; 
 size_t HOST_CCREG ; 
 unsigned int HOST_REGS ; 
 int /*<<< orphan*/  assem_debug (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int can_direct_read (int) ; 
 int /*<<< orphan*/  emit_movimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_movswl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_movswl_indexed (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_readword (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_readword_indexed (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_rorimm (int,int,int) ; 
 int get_reg (scalar_t__*,int /*<<< orphan*/ ) ; 
 int* imm ; 
 int /*<<< orphan*/  map_address (int) ; 
 int* opcode ; 
 int /*<<< orphan*/ * rt1 ; 
 int start ; 

void pcrel_assemble(int i,struct regstat *i_regs)
{
  int t,addr,map=-1,cache=-1;
  int offset;
  int jaddr=0;
  int memtarget,c=0,constaddr;
  unsigned int hr;
  u32 reglist=0;
  t=get_reg(i_regs->regmap,rt1[i]);
  offset=imm[i];
  for(hr=0;hr<HOST_REGS;hr++) {
    if(i_regs->regmap[hr]>=0) reglist|=1<<hr;
  }
  if(i_regs->regmap[HOST_CCREG]==CCREG) reglist&=~(1<<HOST_CCREG);
  if(t>=0) {
    if(!((i_regs->isdoingcp>>t)&1)) {
      int jaddr=0;
      // This is to handle the exceptional case where we can not do constant propagation
      assert(opcode[i]!=12); // MOVA should always be able to do constant propagation
      constaddr=((start+i*2+4)&~3)+imm[i];
      if(opcode[i]==9) constaddr=(start+i*2+4)+imm[i]; // MOV.W
      assem_debug("Can't do constant propagation, doing PC-relatve load\n");
      //int map=get_reg(i_regs->regmap,MOREG);
      //int cache=get_reg(i_regs->regmap,MMREG);
      //assert(map>=0);
      reglist&=~(1<<t);
      //reglist&=~(1<<map);
      assert(can_direct_read(constaddr));
      #ifndef HOST_IMM_ADDR32
      emit_movimm(map_address(constaddr),t);
      #endif
      //map=do_map_r(t,-1,map,cache,0,-1,-1,0,0);
      //do_map_r_branch(map,0,0,&jaddr);
      //assert(jaddr);
      if(opcode[i]==9) { // MOV.W
        // direct load
        #ifdef HOST_IMM_ADDR32
        emit_movswl(map_address(constaddr),t);
        #else
        //emit_movswl_indexed_map(0,t,map,t);
        emit_movswl_indexed(0,t,t);
        #endif
        //add_stub(LOADW_STUB,jaddr,(int)out,i,t,(int)(i_regs),ccadj[i],reglist);
      }
      else { // MOV.L
        // direct load
        #ifdef HOST_IMM_ADDR32
        emit_readword(map_address(constaddr),t);
        #else
        //emit_readword_indexed_map(0,t,map,t);
        emit_readword_indexed(0,t,t);
        #endif
        emit_rorimm(t,16,t);
        //add_stub(LOADL_STUB,jaddr,(int)out,i,t,(int)(i_regs),ccadj[i],reglist);
      }
    }
  }
}