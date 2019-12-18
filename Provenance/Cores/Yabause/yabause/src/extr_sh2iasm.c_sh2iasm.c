#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ reg; scalar_t__ type; } ;
typedef  TYPE_1__ sh_operand_info ;
typedef  int /*<<< orphan*/  sh_opcode_info ;

/* Variables and functions */
 int /*<<< orphan*/  asm_bad (char*,char*) ; 
 int build_bytes (int /*<<< orphan*/ ,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  parse_arg (char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rebuild_args (char*,char*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  search_op (char*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int strip_arg (char*,char*) ; 
 int strip_opname (char*,char*) ; 
 char tolower (char) ; 

int sh2iasm(char *str, char *err_msg)

// Function to do all the work

{
   char name[30];
   char arg1[30];
   char arg2[30];
   char *p;
   int loop;
   int oplen,arg1len,arg2len;
   sh_operand_info arg1info,arg2info,disp;
   sh_opcode_info opcode;

   arg1info.type = 0;
   arg1info.reg = 0;
   arg2info.type = 0;
   arg2info.reg = 0;
   //gets(str);
   p = str;
   while(*p == ' ')
     p++;

   if((oplen = strip_opname(p,name)) == 0)
    {
       asm_bad("No opcode", err_msg);
       return 0;
    }

   p += oplen;
   while(*p == ' ')
     p++;

   arg1len = strip_arg(p,arg1);
   p += arg1len;

   while(*p == ' ')
     p++;
   if(*p == ',')
     p++;
   while(*p == ' ')
     p++;

   arg2len = strip_arg(p,arg2);

   for(loop = 0;name[loop] != 0;loop++)
   {
       name[loop] = tolower(name[loop]);
   }
   for(loop = 0;arg1[loop] != 0;loop++)
      arg1[loop] = tolower(arg1[loop]);
   for(loop = 0;arg2[loop] != 0;loop++)
      arg2[loop] = tolower(arg2[loop]);

   if(!parse_arg(arg1,&arg1info,err_msg))
   {
      if(arg1[0] != 0)
        asm_bad("Arg 1", err_msg);
      return 0;
   }
   if(!parse_arg(arg2,&arg2info,err_msg))
   {
      if(arg2[0] != 0)
        asm_bad("Arg 2", err_msg);
      return 0;
   }

   if(!search_op(name,&arg1info,&arg2info,&opcode))
   {
     asm_bad("Invalid opcode. Likely doesn't exist or format is wrong\n", err_msg);
     return 0;
   }

   loop = 0;
   rebuild_args(arg1,arg2,&arg1info,&arg2info,&disp);
   return build_bytes(opcode,arg1info,arg2info,disp);
}