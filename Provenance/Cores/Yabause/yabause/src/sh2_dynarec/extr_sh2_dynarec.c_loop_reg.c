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
struct TYPE_2__ {int /*<<< orphan*/  regmap_entry; } ;

/* Variables and functions */
 scalar_t__ CJUMP ; 
 scalar_t__ RJUMP ; 
 scalar_t__ SJUMP ; 
 scalar_t__ UJUMP ; 
 scalar_t__* ba ; 
 int get_reg (int /*<<< orphan*/ ,int) ; 
 scalar_t__* itype ; 
 TYPE_1__* regs ; 
 int slen ; 
 scalar_t__ start ; 
 int* unneeded_reg ; 

int loop_reg(int i, int r, int hr)
{
  int j,k;
  for(j=0;j<9;j++)
  {
    if(i+j>=slen) {
      j=slen-i-1;
      break;
    }
    if(itype[i+j]==UJUMP||itype[i+j]==RJUMP)
    {
      // Don't go past an unconditonal jump
      j++;
      break;
    }
  }
  k=0;
  if(i>0){
    if(itype[i-1]==UJUMP||itype[i-1]==CJUMP||itype[i-1]==SJUMP)
      k--;
  }
  for(;k<j;k++)
  {
    if(r<64&&((unneeded_reg[i+k]>>r)&1)) return hr;
    if(i+k>=0&&(itype[i+k]==UJUMP||itype[i+k]==CJUMP||itype[i+k]==SJUMP))
    {
      if(ba[i+k]>=start && ba[i+k]<(start+i*2))
      {
        int t=(ba[i+k]-start)>>1;
        int reg=get_reg(regs[t].regmap_entry,r);
        if(reg>=0) return reg;
        //reg=get_reg(regs[t+1].regmap_entry,r);
        //if(reg>=0) return reg;
      }
    }
  }
  return hr;
}