#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int const type; int reg; } ;
typedef  TYPE_1__ sh_operand_info ;
struct TYPE_8__ {int* nibbles; } ;
typedef  TYPE_2__ sh_opcode_info ;

/* Variables and functions */
#define  BRANCH_12 141 
#define  BRANCH_8 140 
#define  DISP_4 139 
#define  DISP_8 138 
#define  IMM_4 137 
#define  IMM_4BY2 136 
#define  IMM_4BY4 135 
#define  IMM_8 134 
#define  IMM_8BY2 133 
#define  IMM_8BY4 132 
#define  PCRELIMM_8BY2 131 
#define  PCRELIMM_8BY4 130 
#define  REG_M 129 
#define  REG_N 128 
 int /*<<< orphan*/  insert (unsigned int*,int,int) ; 

unsigned long build_bytes(sh_opcode_info op,sh_operand_info a1,
                          sh_operand_info a2,sh_operand_info disp)

// Now we know the opcode then build its bytes. Returns opcode if valid
// and 0 if not.

{
    int loop;
    int i;
    unsigned int opcode;

    loop = 0;
    opcode = 0;
    while(loop < 4)
    {
       i = op.nibbles[loop];
       if(i < 16)
       {
          insert(&opcode,i,loop);
          loop++;
       }
       else
       {
          switch(i)
          {
            case REG_M   : if(a1.type == REG_M)
                             insert(&opcode,a1.reg,loop);
                           else
                             insert(&opcode,a2.reg,loop);
                           break;
            case REG_N   : if(a1.type == REG_N)
                             insert(&opcode,a1.reg,loop);
                           else
                             insert(&opcode,a2.reg,loop);
                           break;
            case DISP_4  :
            case IMM_4   : insert(&opcode,disp.reg&0xF,loop);
                           break;
            case IMM_4BY2: disp.reg >>= 1;
                           insert(&opcode,disp.reg&0xF,loop);
                           break;
            case IMM_4BY4: disp.reg >>= 2;
                           insert(&opcode,disp.reg&0xF,loop);
                           break;
            case BRANCH_12: insert(&opcode,(disp.reg >> 8) & 0xF,loop);
                            insert(&opcode,(disp.reg >> 4) & 0xF,loop+1);
                            insert(&opcode,disp.reg & 0xF,loop+2);
                            loop += 2;
                            break;
            case DISP_8   :
            case IMM_8    :
            case BRANCH_8 : insert(&opcode,(disp.reg >> 4) & 0xF,loop);
                            insert(&opcode,disp.reg & 0xF,loop+1);
                            loop += 1;
                            break;
            case PCRELIMM_8BY2:
            case IMM_8BY2 :
                            disp.reg >>= 1;
                            insert(&opcode,(disp.reg >> 4) & 0xF,loop);
                            insert(&opcode,disp.reg & 0xF,loop+1);
                            loop += 1;
                            break;
            case PCRELIMM_8BY4:
            case IMM_8BY4 :
                            disp.reg >>= 2;
                            insert(&opcode,(disp.reg >> 4) & 0xF,loop);
                            insert(&opcode,disp.reg & 0xF,loop+1);
                            loop += 1;
                            break;
          }
          loop++;
       }
    }
    return opcode;
}