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
struct regstat {scalar_t__* regmap; int wasdoingcp; long long u; } ;

/* Variables and functions */
 scalar_t__ GBRIND ; 
 unsigned int HOST_REGS ; 
 int MMREG ; 
 int MOREG ; 
 int RMWA_STUB ; 
 int RMWO_STUB ; 
 int RMWT_STUB ; 
 int RMWX_STUB ; 
 int SR ; 
 long long TBIT ; 
 int /*<<< orphan*/  add_stub (int,int,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__* addrmode ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * ccadj ; 
 int** cpmap ; 
 int do_map_w (int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  do_map_w_branch (int,int,int,int*) ; 
 int /*<<< orphan*/  emit_rmw_andimm (int,int,int) ; 
 int /*<<< orphan*/  emit_rmw_orimm (int,int,int) ; 
 int /*<<< orphan*/  emit_rmw_xorimm (int,int,int) ; 
 int /*<<< orphan*/  emit_sh2tas (int,int,char) ; 
 void* get_reg (scalar_t__*,int) ; 
 int* imm ; 
 int* opcode2 ; 
 scalar_t__ out ; 
 int* rs1 ; 
 int* rs2 ; 
 long long* rt1 ; 

void rmw_assemble(int i,struct regstat *i_regs)
{
  int s,o,t,addr,map=-1,cache=-1;
  int jaddr=0;
  int type;
  int memtarget,c=0,constaddr;
  int dualindex=(addrmode[i]==GBRIND);
  unsigned int hr;
  u32 reglist=0;
  t=get_reg(i_regs->regmap,-1);
  s=get_reg(i_regs->regmap,rs1[i]);
  o=get_reg(i_regs->regmap,rs2[i]);
  for(hr=0;hr<HOST_REGS;hr++) {
    if(i_regs->regmap[hr]>=0) reglist|=1<<hr;
  }
  if(s>=0) {
    if(dualindex)
      c=(i_regs->wasdoingcp>>s)&(i_regs->wasdoingcp>>o)&1;
    else
      c=(i_regs->wasdoingcp>>s)&1;
    if(c) {
      if(dualindex)
         constaddr=cpmap[i][s]+cpmap[i][o];
      else
         constaddr=cpmap[i][s];
    }
    //printf("constaddr=%x offset=%x\n",constaddr,offset);
    memtarget=1; // FIXME
  }
  if(dualindex||s<0||c) addr=t;
  else addr=s;
  assert(t>=0);
  reglist&=~(1<<t);
  {
    int x=0;
    if (!c) x=1; // MOV.B
    map=get_reg(i_regs->regmap,MOREG);
    cache=get_reg(i_regs->regmap,MMREG);
    assert(map>=0);
    reglist&=~(1<<map);
    map=do_map_w(addr,t,map,cache,x,c,constaddr);
    if (!c) addr=t; // MOV.B
    do_map_w_branch(map,c,constaddr,&jaddr);
  }
  if(opcode2[i]==11) type=RMWT_STUB; // TAS.B
  if(opcode2[i]==13) type=RMWA_STUB; // AND.B
  if(opcode2[i]==14) type=RMWX_STUB; // XOR.B
  if(opcode2[i]==15) type=RMWO_STUB; // OR.B
  if(!c||memtarget) {
    if(opcode2[i]==11) { // TAS.B
      signed char sr;
      sr=get_reg(i_regs->regmap,SR);
      assert(sr>=0); // Liveness analysis?
      assert(rt1[i]==TBIT);
      if(sr>=0&&!(i_regs->u&(1LL<<TBIT))) emit_sh2tas(addr,map,sr);
      else emit_rmw_orimm(addr,map,0x80); // T ignored, set only
    }
    if(opcode2[i]==13) emit_rmw_andimm(addr,map,imm[i]); // AND.B
    if(opcode2[i]==14) emit_rmw_xorimm(addr,map,imm[i]); // XOR.B
    if(opcode2[i]==15) emit_rmw_orimm(addr,map,imm[i]); // OR.B
  }
  if(jaddr)
    add_stub(type,jaddr,(int)out,i,addr,(int)i_regs,ccadj[i],reglist);
}