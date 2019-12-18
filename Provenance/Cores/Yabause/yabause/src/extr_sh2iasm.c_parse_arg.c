#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ sh_operand_info ;

/* Variables and functions */
 int A_BDISP12 ; 
 int A_IMM ; 
 int parse_at (char const*,TYPE_1__*,char*) ; 
 int parse_reg (char const*,int*,int /*<<< orphan*/ *) ; 

int parse_arg(const char *arg,sh_operand_info *op, char *err_msg)

// Parse arg and return a filled operand struct

{
    int len,mode;

    if(arg[0] == 0)
    {
      op->type = 0;
      op->reg = 0;
      return 1;
    }

    if(*arg == '@')
    {
       arg++;
       return parse_at(arg,op, err_msg);
    }

    if(*arg == '#')
    {
       op->type = A_IMM;
       return 1;
    }

    len = parse_reg(arg,&mode,&(op->reg));
    if(len)
    {
       op->type = mode;
       return 1;
    }
    else
    {
       op->type = A_BDISP12;
       return 1;
    }


    return 0;
}