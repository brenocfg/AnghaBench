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
 int /*<<< orphan*/  DisaGetEa (char*,int,int) ; 
 int /*<<< orphan*/  DisaText ; 
 int* Tasm ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,char*,char*) ; 

__attribute__((used)) static int DisaArithReg(int op)
{
  // 1t0tnnnd xxeeeeee (tt=type:or/sub/and/add xx=size, eeeeee=EA)
  int type=0,size=0,dir=0,rea=0,ea=0;
  char reat[64]="",eat[64]="";
  char *opcode[]={"or","sub","","","and","add"};

  type=(op>>12)&5;
  rea =(op>> 9)&7;
  dir =(op>> 8)&1;
  size=(op>> 6)&3; if (size>=3) return 1;
  ea  = op&0x3f;

  if (dir && ea<0x10) return 1; // addx opcode

  DisaGetEa(reat,rea,size);
  DisaGetEa( eat, ea,size);

  if (dir) sprintf(DisaText,"%s.%c %s, %s",opcode[type],Tasm[size],reat,eat);
  else     sprintf(DisaText,"%s.%c %s, %s",opcode[type],Tasm[size],eat,reat);
  return 0;
}