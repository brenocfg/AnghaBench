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

/* Variables and functions */
 scalar_t__ CJUMP ; 
 scalar_t__ RJUMP ; 
 scalar_t__ SJUMP ; 
 scalar_t__ SYSCALL ; 
 scalar_t__ SYSTEM ; 
 scalar_t__ UJUMP ; 
 int* ba ; 
 scalar_t__* itype ; 
 int* rs1 ; 
 int* rs2 ; 
 int slen ; 
 int start ; 
 int* unneeded_reg ; 

int needed_again(int r, int i)
{
  int j;
  int b=-1;
  int rn=10;
  
  if(i>0&&(itype[i-1]==UJUMP||itype[i-1]==RJUMP))
  {
    if(ba[i-1]<start || ba[i-1]>start+slen*4-4)
      return 0; // Don't need any registers if exiting the block
  }
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
    if(itype[i+j]==SYSCALL||itype[i+j]==SYSTEM) 
    {
      break;
    }
  }
  for(;j>=1;j--)
  {
    if(rs1[i+j]==r) rn=j;
    if(rs2[i+j]==r) rn=j;
    if((unneeded_reg[i+j]>>r)&1) rn=10;
    if(i+j>=0&&(itype[i+j]==UJUMP||itype[i+j]==CJUMP||itype[i+j]==SJUMP))
    {
      b=j;
    }
  }
  /*
  if(b>=0)
  {
    if(ba[i+b]>=start && ba[i+b]<(start+slen*4))
    {
      // Follow first branch
      int o=rn;
      int t=(ba[i+b]-start)>>2;
      j=7-b;if(t+j>=slen) j=slen-t-1;
      for(;j>=0;j--)
      {
        if(!((unneeded_reg[t+j]>>r)&1)) {
          if(rs1[t+j]==r) if(rn>j+b+2) rn=j+b+2;
          if(rs2[t+j]==r) if(rn>j+b+2) rn=j+b+2;
        }
        else rn=o;
      }
    }
  }*/
  if(rn<10) return 1;
  return 0;
}