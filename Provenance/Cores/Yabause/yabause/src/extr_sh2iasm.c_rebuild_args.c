#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; void* reg; } ;
typedef  TYPE_1__ sh_operand_info ;

/* Variables and functions */
#define  A_BDISP12 144 
#define  A_BDISP8 143 
#define  A_DEC_M 142 
#define  A_DEC_N 141 
#define  A_DISP_GBR 140 
#define  A_DISP_PC 139 
#define  A_DISP_REG_M 138 
#define  A_DISP_REG_N 137 
#define  A_IMM 136 
#define  A_INC_M 135 
#define  A_INC_N 134 
#define  A_IND_M 133 
#define  A_IND_N 132 
#define  A_IND_R0_REG_M 131 
#define  A_IND_R0_REG_N 130 
#define  A_REG_M 129 
#define  A_REG_N 128 
 void* IMM ; 
 void* PCRELIMM ; 
 void* REG_M ; 
 void* REG_N ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 void* strtol (char*,char**,int) ; 

int rebuild_args(const char *arg1,const char *arg2,sh_operand_info *a1,
                  sh_operand_info *a2,sh_operand_info *disp)

// Rebuild args into the maximum 3 args for building.
// Redefine type values to nibble equivalents and extract imm values.
// returns 1 on error

{
   char s1[30],s2[30];
   char *bp;

   strcpy(s1,arg1);
   strcpy(s2,arg2);
   bp = NULL;

   switch(a1->type)
   {
     case A_IND_R0_REG_M:
     case A_DEC_M:
     case A_INC_M:
     case A_IND_M:
     case A_REG_M: a1->type = REG_M;
                   break;
     case A_IND_R0_REG_N:
     case A_DEC_N:
     case A_INC_N:
     case A_IND_N:
     case A_REG_N: a1->type = REG_N;
                   break;
     case A_DISP_PC: disp->reg = strtol(&s1[2],&bp,16);
                     disp->type = PCRELIMM;
                     break;
     case A_DISP_GBR:disp->reg = strtol(&s1[2],&bp,16);
                     disp->type = IMM;
                     break;
     case A_DISP_REG_M: disp->reg = strtol(&s1[2],&bp,16);
                        disp->type = IMM;
                        a1->type = REG_M;
                        break;
     case A_DISP_REG_N: disp->reg = strtol(&s1[2],&bp,16);
                        disp->type = IMM;
                        a1->type = REG_N;
                        break;
     case A_IMM       : disp->reg = strtol(&s1[1],&bp,16);
                        disp->type = IMM;
                        break;
     case A_BDISP12   :
     case A_BDISP8    : disp->reg = strtol(s1,&bp,16);
                        disp->type = IMM;
                        break;

   }

   switch(a2->type)
   {
     case A_IND_R0_REG_M:
     case A_DEC_M:
     case A_INC_M:
     case A_IND_M:
     case A_REG_M: a2->type = REG_M;

                   break;
     case A_IND_R0_REG_N:
     case A_DEC_N:
     case A_INC_N:
     case A_IND_N:
     case A_REG_N: a2->type = REG_N;

                   break;
     case A_DISP_PC: disp->reg = strtol(&s2[2],&bp,16);
                     disp->type = PCRELIMM;
                     break;
     case A_DISP_GBR:disp->reg = strtol(&s2[2],&bp,16);
                     disp->type = IMM;
                     break;
     case A_DISP_REG_M: disp->reg = strtol(&s2[2],&bp,16);
                        disp->type = IMM;
                        a2->type = REG_M;
                        break;
     case A_DISP_REG_N: disp->reg = strtol(&s2[2],&bp,16);
                        disp->type = IMM;
                        a2->type = REG_N;
                        break;
     case A_IMM       : disp->reg = strtol(&s2[1],&bp,16);
                        disp->type = IMM;
                        break;
     case A_BDISP12   :
     case A_BDISP8    : disp->reg = strtol(s2,&bp,16);
                        disp->type = IMM;
                        break;
   }

   return 0;
}