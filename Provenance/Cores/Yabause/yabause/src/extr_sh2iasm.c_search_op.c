#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_1__ sh_operand_info ;
struct TYPE_9__ {scalar_t__* arg; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ sh_opcode_info ;

/* Variables and functions */
 scalar_t__ fix_arg (scalar_t__,TYPE_1__*) ; 
 TYPE_2__* sh_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int search_op(const char *name,sh_operand_info *arg1,sh_operand_info *arg2,sh_opcode_info *op)

// Search for a matching opcode and fix args if necessary

{
   int loop = 0;
   sh_operand_info arg1back,arg2back;

   arg1back = *arg1;
   arg2back = *arg2;

   while(strcmp(sh_table[loop].name,"ftrv"))
   {
      if(!strcmp(sh_table[loop].name,name))
      {
         if(sh_table[loop].arg[0] != 0)
         {
            if(fix_arg(sh_table[loop].arg[0],arg1))
               arg1->type = sh_table[loop].arg[0];
         }
         if(sh_table[loop].arg[1] != 0)
         {
            if(fix_arg(sh_table[loop].arg[1],arg2))
               arg2->type = sh_table[loop].arg[1];
         }

         if((arg1->type == sh_table[loop].arg[0]) &&
            (arg2->type == sh_table[loop].arg[1]))
         {
            *op = sh_table[loop];
            return 1;
         }

      }

      *arg1 = arg1back;
      *arg2 = arg2back;
      loop++;
   }

   return 0;
}