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
struct regstat {char* regmap; int dirty; int isdoingcp; int u; } ;
typedef  int /*<<< orphan*/  hsn ;

/* Variables and functions */
 size_t CCREG ; 
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
 int /*<<< orphan*/  lsn (unsigned char*,int,int*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int* rs1 ; 
 int* rs2 ; 
 int* rt1 ; 
 int* rt2 ; 
 int* unneeded_reg ; 

void alloc_reg_temp(struct regstat *cur,int i,signed char reg)
{
  int r,hr;
  int preferred_reg = -1;
  
  // see if it's already allocated
  for(hr=0;hr<HOST_REGS;hr++)
  {
    if(hr!=EXCLUDE_REG&&cur->regmap[hr]==reg) return;
  }
  
  // Try to allocate any available register
  for(hr=HOST_REGS-1;hr>=0;hr--) {
    if(hr!=EXCLUDE_REG&&cur->regmap[hr]==-1) {
      cur->regmap[hr]=reg;
      cur->dirty&=~(1<<hr);
      cur->isdoingcp&=~(1<<hr);
      return;
    }
  }
  
  // Find an unneeded register
  for(hr=HOST_REGS-1;hr>=0;hr--)
  {
    r=cur->regmap[hr];
    if(r>=0) {
      if((cur->u>>r)&1) {
        if(i==0||((unneeded_reg[i-1]>>r)&1)) {
          cur->regmap[hr]=reg;
          cur->dirty&=~(1<<hr);
          cur->isdoingcp&=~(1<<hr);
          return;
        }
      }
    }
  }
  
  // Ok, now we have to evict someone
  // Pick a register we hopefully won't need soon
  // TODO: we might want to follow unconditional jumps here
  // TODO: get rid of dupe code and make this into a function
  unsigned char hsn[MAXREG+1];
  memset(hsn,10,sizeof(hsn));
  int j;
  lsn(hsn,i,&preferred_reg);
  //printf("hsn: %d %d %d %d %d %d %d\n",hsn[cur->regmap[0]&63],hsn[cur->regmap[1]&63],hsn[cur->regmap[2]&63],hsn[cur->regmap[3]&63],hsn[cur->regmap[5]&63],hsn[cur->regmap[6]&63],hsn[cur->regmap[7]&63]);
  if(i>0) {
    // Don't evict the cycle count at entry points, otherwise the entry
    // stub will have to write it.
    if(bt[i]&&hsn[CCREG]>2) hsn[CCREG]=2;
    if(i>1&&hsn[CCREG]>2&&(itype[i-2]==RJUMP||itype[i-2]==UJUMP||itype[i-2]==CJUMP||itype[i-2]==SJUMP)) hsn[CCREG]=2;
    for(j=10;j>=3;j--)
    {
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
  printf("This shouldn't happen");exit(1);
}