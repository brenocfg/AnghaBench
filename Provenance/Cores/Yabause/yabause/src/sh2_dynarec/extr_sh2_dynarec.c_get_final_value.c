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
struct TYPE_2__ {int* regmap; int isdoingcp; int wasdoingcp; } ;

/* Variables and functions */
 scalar_t__ CJUMP ; 
 scalar_t__ DUALIND ; 
 scalar_t__ GBRIND ; 
 scalar_t__ LOAD ; 
 scalar_t__ RJUMP ; 
 scalar_t__ SJUMP ; 
 scalar_t__ UJUMP ; 
 scalar_t__* addrmode ; 
 scalar_t__* bt ; 
 scalar_t__ can_direct_read (int) ; 
 int** cpmap ; 
 int* imm ; 
 scalar_t__* itype ; 
 int map_address (int) ; 
 int* opcode2 ; 
 TYPE_1__* regs ; 
 int* rs1 ; 
 int* rt1 ; 
 int slen ; 
 int* unneeded_reg ; 

int get_final_value(int hr, int i, int *value)
{
  int reg=regs[i].regmap[hr];
  while(i<slen-1) {
    if(regs[i+1].regmap[hr]!=reg) break;
    if(!((regs[i+1].isdoingcp>>hr)&1)) break;
    if(bt[i+1]) break;
    i++;
  }
  if(i<slen-1) {
    if(itype[i]==UJUMP||itype[i]==RJUMP||itype[i]==CJUMP||itype[i]==SJUMP) {
      *value=cpmap[i][hr];
      return 1;
    }
    if(!bt[i+1]) {
      if(itype[i+1]==UJUMP||itype[i+1]==RJUMP||itype[i+1]==SJUMP) {
        // Load in delay slot, out-of-order execution
        if(itype[i+2]==LOAD&&rs1[i+2]==reg&&rt1[i+2]==reg&&((regs[i+1].wasdoingcp>>hr)&1))
        {
          if(addrmode[i+2]==DUALIND||addrmode[i+2]==GBRIND) {
            *value=cpmap[i][hr];
            return 1;
          }
          // Don't load address if can_direct_read and HOST_IMM_ADDR32
          #ifdef HOST_IMM_ADDR32
          if(can_direct_read(cpmap[i][hr]+imm[i+2])) return 0;
          #endif
          // Precompute load address
          *value=cpmap[i][hr]+imm[i+2];
          if(can_direct_read(*value)) *value=map_address(*value);
          if((opcode2[i+2]&3)==0) *value^=1; // byteswap for little-endian
          return 1;
        }
      }
      if(itype[i+1]==LOAD&&rs1[i+1]==reg&&rt1[i+1]==reg)
      {
        if(addrmode[i+1]==DUALIND||addrmode[i+1]==GBRIND) {
          *value=cpmap[i][hr];
          return 1;
        }
        // Don't load address if can_direct_read and HOST_IMM_ADDR32
        #ifdef HOST_IMM_ADDR32
        if(can_direct_read(cpmap[i][hr]+imm[i+1])) return 0;
        #endif
        // Precompute load address
        *value=cpmap[i][hr]+imm[i+1];
        if(can_direct_read(*value)) *value=map_address(*value);
        if((opcode2[i+1]&3)==0) *value^=1; // byteswap for little-endian
        //printf("c=%x imm=%x\n",(int)cpmap[i][hr],imm[i+1]);
        return 1;
      }
    }
  }
  *value=cpmap[i][hr];
  //printf("c=%x\n",(int)cpmap[i][hr]);
  if(i==slen-1) return 1;
  return !((unneeded_reg[i+1]>>reg)&1);
}