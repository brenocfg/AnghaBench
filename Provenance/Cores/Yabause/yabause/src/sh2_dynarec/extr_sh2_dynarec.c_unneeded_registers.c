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
typedef  long long u64 ;

/* Variables and functions */
 scalar_t__ CJUMP ; 
 scalar_t__ RJUMP ; 
 scalar_t__ SJUMP ; 
 long long SR ; 
 scalar_t__ SYSTEM ; 
 int TBIT ; 
 scalar_t__ UJUMP ; 
 scalar_t__* ba ; 
 long long* branch_unneeded_reg ; 
 scalar_t__* itype ; 
 int* opcode ; 
 long long* rs1 ; 
 long long* rs2 ; 
 long long* rs3 ; 
 long long* rt1 ; 
 long long* rt2 ; 
 int slen ; 
 int* source ; 
 scalar_t__ start ; 
 long long* unneeded_reg ; 

void unneeded_registers(int istart,int iend,int r)
{
  int i;
  u64 u,uu,b,bu;
  u64 temp_u,temp_uu;
  u64 tdep;
  if(iend==slen-1) {
    u=0;
  }else{
    u=unneeded_reg[iend+1];
    u=0;
  }
  for (i=iend;i>=istart;i--)
  {
    //printf("unneeded registers i=%d (%d,%d) r=%d\n",i,istart,iend,r);
    if(itype[i]==RJUMP||itype[i]==UJUMP||itype[i]==CJUMP||itype[i]==SJUMP)
    {
      if(ba[i]<start || ba[i]>=(start+slen*2))
      {
        // Branch out of this block, flush all regs
        u=0;
        branch_unneeded_reg[i]=u;
        if(itype[i]!=CJUMP) {
          // Merge in delay slot
          if(rt1[i+1]>=0) u|=1LL<<rt1[i+1];
          if(rt2[i+1]>=0) u|=1LL<<rt2[i+1];
          if(rs1[i+1]>=0) u&=~(1LL<<rs1[i+1]);
          if(rs2[i+1]>=0) u&=~(1LL<<rs2[i+1]);
          if(rs3[i+1]>=0) u&=~(1LL<<rs3[i+1]);
        }
      }
      else
      {
        if(ba[i]<=start+i*2) {
          // Backward branch
          if(itype[i]==UJUMP||itype[i]==RJUMP)
          {
            // Unconditional branch
            temp_u=0;
          } else if(itype[i]==CJUMP) {
            // Conditional branch (not taken case)
            temp_u=unneeded_reg[i+1];
          } else {
            // Conditional branch (not taken case)
            temp_u=unneeded_reg[i+2];
          }
          if(itype[i]!=CJUMP) {
            // Merge in delay slot
            if(rt1[i+1]>=0) temp_u|=1LL<<rt1[i+1];
            if(rt2[i+1]>=0) temp_u|=1LL<<rt2[i+1];
            if(rs1[i+1]>=0) temp_u&=~(1LL<<rs1[i+1]);
            if(rs2[i+1]>=0) temp_u&=~(1LL<<rs2[i+1]);
            if(rs3[i+1]>=0) temp_u&=~(1LL<<rs3[i+1]);
          }
          if(rt1[i]>=0) temp_u|=1LL<<rt1[i];
          if(rt2[i]>=0) temp_u|=1LL<<rt2[i];
          if(rs1[i]>=0) temp_u&=~(1LL<<rs1[i]);
          if(rs2[i]>=0) temp_u&=~(1LL<<rs2[i]);
          if(rs3[i]>=0) temp_u&=~(1LL<<rs3[i]);
          unneeded_reg[i]=temp_u;
          // Only go three levels deep.  This recursion can take an
          // excessive amount of time if there are a lot of nested loops.
          if(r<2) {
            unneeded_registers((ba[i]-start)>>1,i-1,r+1);
          }else{
            unneeded_reg[(ba[i]-start)>>1]=0;
          }
        } /*else*/ if(1) {
          if(itype[i]==UJUMP||itype[i]==RJUMP)
          {
            // Unconditional branch
            u=unneeded_reg[(ba[i]-start)>>1];
            // Always need stack and status in case of interrupt
            u&=~((1LL<<15)|(1LL<<SR));
            branch_unneeded_reg[i]=u;
        //u=0; // for debugging
        //branch_unneeded_reg[i]=u; // for debugging
            // Merge in delay slot
            if(rt1[i+1]>=0) u|=1LL<<rt1[i+1];
            if(rt2[i+1]>=0) u|=1LL<<rt2[i+1];
            if(rs1[i+1]>=0) u&=~(1LL<<rs1[i+1]);
            if(rs2[i+1]>=0) u&=~(1LL<<rs2[i+1]);
            if(rs3[i+1]>=0) u&=~(1LL<<rs3[i+1]);
          } else {
            // Conditional branch
            b=unneeded_reg[(ba[i]-start)>>1];
            branch_unneeded_reg[i]=b;
        //b=0; // for debugging
        //branch_unneeded_reg[i]=b; // for debugging
            // Branch delay slot
            if(itype[i]!=CJUMP) {
              if(rt1[i+1]>=0) b|=1LL<<rt1[i+1];
              if(rt2[i+1]>=0) b|=1LL<<rt2[i+1];
              if(rs1[i+1]>=0) b&=~(1LL<<rs1[i+1]);
              if(rs2[i+1]>=0) b&=~(1LL<<rs2[i+1]);
              if(rs3[i+1]>=0) b&=~(1LL<<rs3[i+1]);
            }
            u&=b;
            // Always need stack and status in case of interrupt
            u&=~((1LL<<15)|(1LL<<SR));
        //u=0; // for debugging
            if(itype[i]!=CJUMP) {
              if(i<slen-1) {
                branch_unneeded_reg[i]&=unneeded_reg[i+2];
              } else {
                branch_unneeded_reg[i]=0;
              }
            }else{
              if(i<slen) {
                branch_unneeded_reg[i]&=unneeded_reg[i+1];
              } else {
                branch_unneeded_reg[i]=0;
              }
            }
        //branch_unneeded_reg[i]=0; // for debugging
          }
        }
      }
    }
    else if(itype[i]==RJUMP && source[i]==0x2b)
    {
      // RTE instruction (return from exception)
      u=(1<<SR);
    }
    else if(itype[i]==SYSTEM && opcode[i]==12)
    {
      // TRAPA instruction (syscall)
      u=0;
    }
    //u=uu=0; // DEBUG
    //tdep=(~uu>>rt1[i])&1;
    // Written registers are unneeded
    if(rt1[i]>=0) u|=1LL<<rt1[i];
    if(rt2[i]>=0) u|=1LL<<rt2[i];
    // Accessed registers are needed
    if(rs1[i]>=0) u&=~(1LL<<rs1[i]);
    if(rs2[i]>=0) u&=~(1LL<<rs2[i]);
    if(rs3[i]>=0) u&=~(1LL<<rs3[i]);
    // Source-target dependencies
    //uu&=~(tdep<<dep1[i]);
    //uu&=~(tdep<<dep2[i]);
    if(u&(1<<SR)) u|=(1<<TBIT);
    // Save it
    unneeded_reg[i]=u;
  }
}