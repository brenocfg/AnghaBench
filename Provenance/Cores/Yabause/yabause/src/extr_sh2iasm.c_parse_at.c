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
struct TYPE_3__ {int type; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ sh_operand_info ;

/* Variables and functions */
 int A_DEC_N ; 
 int A_DISP_GBR ; 
 int A_DISP_PC ; 
 int A_DISP_REG_N ; 
 int A_GBR ; 
 int A_INC_N ; 
 int A_IND_N ; 
 int A_IND_R0_REG_N ; 
 int A_R0_GBR ; 
 int A_REG_N ; 
 int /*<<< orphan*/  asm_bad (char*,char*) ; 
 int parse_reg (char const*,int*,int /*<<< orphan*/ *) ; 

int parse_at(const char *arg,sh_operand_info *op, char *err_msg)

// Parse pointer arguement and return a operand info struct

{
    int mode;
    int len;

    if(arg[0] == 0)
      return 0;

    if(*arg == '-')
    {
       arg++;
       len = parse_reg(arg,&mode,&(op->reg));
       if(len == 0)
       {
          asm_bad("Cant find arg", err_msg);
          return 0;
       }
       if(mode != A_REG_N)
       {
          asm_bad("Invalid reg after @-", err_msg);
          return 0;
       }
       else
       {
          op->type = A_DEC_N;
       }
    }
    else
     if(*arg == '(')
     {
        arg++;
        len = parse_reg(arg,&mode,&(op->reg));
        if((len > 0) && (mode == A_REG_N))
        {
           arg+=len;
           if(op->reg != 0)
           {
              asm_bad("Must be @(R0,...)", err_msg);
              return 0;
           }
           if(arg[0] == ',')
              arg++;
           len = parse_reg(arg,&mode,&(op->reg));
           arg += len;
           if(mode == A_GBR)
           {
              op->type = A_R0_GBR;
           }
           else if (mode == A_REG_N)
           {
              op->type = A_IND_R0_REG_N;
           }
           else
           {
              asm_bad("Syntax error in @(R0,...)", err_msg);
              return 0;
           }

        }
        else
        {
           while((*(arg-1) != ',') && (*arg != 0))
              arg++;
           len = parse_reg(arg,&mode,&(op->reg));
           arg+=len;
           if(len)
           {
             if(mode == A_REG_N)
             {
                op->type = A_DISP_REG_N;
             }
             else if (mode == A_GBR)
             {
                op->type = A_DISP_GBR;
             }
             else if (mode == A_DISP_PC)
             {
                op->type = A_DISP_PC;
             }
             else
             {
                asm_bad("Bad syntax in @(disp,[Rn,GBR,PC])", err_msg);
                return 0;
             }
           }
           else
           {
              asm_bad("Bad syntax in @(disp,[Rn,GBR,PC])", err_msg);
              return 0;
           }
        }
        if(*arg != ')')
        {
          asm_bad("Expected a )", err_msg);
          return 0;
        }
     }
     else
     {
        arg += parse_reg(arg,&mode,&(op->reg));
        if(mode != A_REG_N)
        {
           asm_bad("Invalid register after @", err_msg);
           return 0;
        }
        if(arg[0] == '+')
        {
           op->type = A_INC_N;
        }
        else
        {
           op->type = A_IND_N;
        }
     }

    return 1;
}