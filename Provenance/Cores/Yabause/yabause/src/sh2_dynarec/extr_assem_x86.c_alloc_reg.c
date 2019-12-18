#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regstat {char u; char* regmap; int dirty; int isdoingcp; } ;
typedef  int /*<<< orphan*/  hsn ;
struct TYPE_2__ {int* regmap; } ;

/* Variables and functions */
 char CCREG ; 
 scalar_t__ CJUMP ; 
 int EXCLUDE_REG ; 
 int HOST_CCREG ; 
 int HOST_REGS ; 
 int MAXREG ; 
 scalar_t__ RJUMP ; 
 scalar_t__ SJUMP ; 
 scalar_t__ UJUMP ; 
 scalar_t__* bt ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* itype ; 
 int loop_reg (int,char,int) ; 
 int /*<<< orphan*/  lsn (unsigned char*,int,int*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* regs ; 
 int* rs1 ; 
 int* rs2 ; 
 int* rt1 ; 
 int* rt2 ; 
 int* unneeded_reg ; 

void alloc_reg(struct regstat *cur,int i,signed char reg)
{
  int r,hr;
  int preferred_reg = (reg&3)+(reg>21)*4+(reg==24)+(reg==28)+(reg==32);
  if(reg==CCREG) preferred_reg=HOST_CCREG;
  
  // Don't allocate unused registers
  if((cur->u>>reg)&1) return;
  
  // see if it's already allocated
  for(hr=0;hr<HOST_REGS;hr++)
  {
    if(cur->regmap[hr]==reg) return;
  }
  
  // Keep the same mapping if the register was already allocated in a loop
  preferred_reg = loop_reg(i,reg,preferred_reg);
  
  // Try to allocate the preferred register
  if(cur->regmap[preferred_reg]==-1) {
    cur->regmap[preferred_reg]=reg;
    cur->dirty&=~(1<<preferred_reg);
    cur->isdoingcp&=~(1<<preferred_reg);
    return;
  }
  r=cur->regmap[preferred_reg];
  if(r<64&&((cur->u>>r)&1)) {
    cur->regmap[preferred_reg]=reg;
    cur->dirty&=~(1<<preferred_reg);
    cur->isdoingcp&=~(1<<preferred_reg);
    return;
  }
  
  // Try to allocate EAX, EBX, ECX, or EDX
  // We prefer these because they can do byte and halfword loads
  for(hr=0;hr<4;hr++) {
    if(cur->regmap[hr]==-1) {
      cur->regmap[hr]=reg;
      cur->dirty&=~(1<<hr);
      cur->isdoingcp&=~(1<<hr);
      return;
    }
  }
  
  // Clear any unneeded registers
  // We try to keep the mapping consistent, if possible, because it
  // makes branches easier (especially loops).  So we try to allocate
  // first (see above) before removing old mappings.  If this is not
  // possible then go ahead and clear out the registers that are no
  // longer needed.
  for(hr=0;hr<HOST_REGS;hr++)
  {
    r=cur->regmap[hr];
    if(r>=0) {
      if((cur->u>>r)&1)
        if(i==0||(unneeded_reg[i-1]>>r)&1) {cur->regmap[hr]=-1;break;}
    }
  }
  // Try to allocate any available register, but prefer
  // registers that have not been used recently.
  if(i>0) {
    for(hr=0;hr<HOST_REGS;hr++) {
      if(hr!=EXCLUDE_REG&&cur->regmap[hr]==-1) {
        if(regs[i-1].regmap[hr]!=rs1[i-1]&&regs[i-1].regmap[hr]!=rs2[i-1]&&regs[i-1].regmap[hr]!=rt1[i-1]&&regs[i-1].regmap[hr]!=rt2[i-1]) {
          cur->regmap[hr]=reg;
          cur->dirty&=~(1<<hr);
          cur->isdoingcp&=~(1<<hr);
          return;
        }
      }
    }
  }
  // Try to allocate any available register
  for(hr=0;hr<HOST_REGS;hr++) {
    if(hr!=EXCLUDE_REG&&cur->regmap[hr]==-1) {
      cur->regmap[hr]=reg;
      cur->dirty&=~(1<<hr);
      cur->isdoingcp&=~(1<<hr);
      return;
    }
  }
  
  // Ok, now we have to evict someone
  // Pick a register we hopefully won't need soon
  unsigned char hsn[MAXREG+1];
  memset(hsn,10,sizeof(hsn));
  int j;
  lsn(hsn,i,&preferred_reg);
  //printf("hsn(%x): %d %d %d %d %d %d %d\n",start+i*4,hsn[cur->regmap[0]&63],hsn[cur->regmap[1]&63],hsn[cur->regmap[2]&63],hsn[cur->regmap[3]&63],hsn[cur->regmap[5]&63],hsn[cur->regmap[6]&63],hsn[cur->regmap[7]&63]);
  if(i>0) {
    // Don't evict the cycle count at entry points, otherwise the entry
    // stub will have to write it.
    if(bt[i]&&hsn[CCREG]>2) hsn[CCREG]=2;
    if(i>1&&hsn[CCREG]>2&&(itype[i-2]==RJUMP||itype[i-2]==UJUMP||itype[i-2]==CJUMP||itype[i-2]==SJUMP)) hsn[CCREG]=2;
    for(j=10;j>=3;j--)
    {
      // Alloc preferred register if available
      if(hsn[r=cur->regmap[preferred_reg]&63]==j) {
        for(hr=0;hr<HOST_REGS;hr++) {
          // Evict both parts of a 64-bit register
          if((cur->regmap[hr]&63)==r) {
            cur->regmap[hr]=-1;
            cur->dirty&=~(1<<hr);
            cur->isdoingcp&=~(1<<hr);
          }
        }
        cur->regmap[preferred_reg]=reg;
        return;
      }
      for(r=0;r<=MAXREG;r++)
      {
        if(hsn[r]==j&&r!=rs1[i-1]&&r!=rs2[i-1]&&r!=rt1[i-1]&&r!=rt2[i-1]) {
          for(hr=0;hr<HOST_REGS;hr++) {
            if(hr!=HOST_CCREG||j<hsn[CCREG]) {
              if(cur->regmap[hr]==r+64) {
                cur->regmap[hr]=reg;
                cur->dirty&=~(1<<hr);
                cur->isdoingcp&=~(1<<hr);
                return;
              }
            }
          }
          for(hr=0;hr<HOST_REGS;hr++) {
            if(hr!=HOST_CCREG||j<hsn[CCREG]) {
              if(cur->regmap[hr]==r) {
                cur->regmap[hr]=reg;
                cur->dirty&=~(1<<hr);
                cur->isdoingcp&=~(1<<hr);
                return;
              }
            }
          }
        }
      }
    }
  }
  for(j=10;j>=0;j--)
  {
    for(r=0;r<=MAXREG;r++)
    {
      if(hsn[r]==j) {
        for(hr=0;hr<HOST_REGS;hr++) {
          if(cur->regmap[hr]==r+64) {
            cur->regmap[hr]=reg;
            cur->dirty&=~(1<<hr);
            cur->isdoingcp&=~(1<<hr);
            return;
          }
        }
        for(hr=0;hr<HOST_REGS;hr++) {
          if(cur->regmap[hr]==r) {
            cur->regmap[hr]=reg;
            cur->dirty&=~(1<<hr);
            cur->isdoingcp&=~(1<<hr);
            return;
          }
        }
      }
    }
  }
  printf("This shouldn't happen (alloc_reg)");exit(1);
}