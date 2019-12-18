#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; scalar_t__ reg; } ;
typedef  TYPE_1__ sh_operand_info ;

/* Variables and functions */
 scalar_t__ A_BDISP12 ; 
 int A_BDISP8 ; 
 int A_DEC_M ; 
 scalar_t__ A_DEC_N ; 
 int A_DISP_REG_M ; 
 scalar_t__ A_DISP_REG_N ; 
 int A_INC_M ; 
 scalar_t__ A_INC_N ; 
 int A_IND_M ; 
 scalar_t__ A_IND_N ; 
 int A_IND_R0_REG_M ; 
 scalar_t__ A_IND_R0_REG_N ; 
 int A_R0 ; 
 int A_REG_M ; 
 scalar_t__ A_REG_N ; 

int fix_arg(int type,sh_operand_info *arg)

// Checks the arg with the opcode type and see if its matchable
// Returns 1 if possible to match and 0 if not

{
   if((type == A_DEC_M) && (arg->type == A_DEC_N))
     return 1;
   if((type == A_DISP_REG_M) && (arg->type == A_DISP_REG_N))
     return 1;
   if((type == A_INC_M) && (arg->type == A_INC_N))
     return 1;
   if((type == A_IND_M) && (arg->type == A_IND_N))
     return 1;
   if((type == A_IND_R0_REG_M) && (arg->type == A_IND_R0_REG_N))
     return 1;
   if((type == A_REG_M) && (arg->type == A_REG_N))
     return 1;
   if((type == A_BDISP8) && (arg->type == A_BDISP12))
     return 1;
   if((type == A_R0) && (arg->type == A_REG_N) && (arg->reg == 0))
     return 1;

   return 0;
}