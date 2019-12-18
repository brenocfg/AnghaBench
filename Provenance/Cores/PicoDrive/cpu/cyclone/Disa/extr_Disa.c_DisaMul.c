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
 char** Tasm ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char,char*,char*,char*) ; 

__attribute__((used)) static int DisaMul(int op)
{
  // Div/Mul: 1m00nnns 11eeeeee (m=Mul, nnn=Register Dn, s=signed, eeeeee=EA)
  int type=0,rea=0,sign=0,ea=0,size=1;
  char reat[64]="",eat[64]="";
  char *opcode[2]={"div","mul"};

  type=(op>>14)&1; // div/mul
  rea =(op>> 9)&7;
  sign=(op>> 8)&1;
  ea  = op&0x3f;

  DisaGetEa(reat,rea,size);
  DisaGetEa( eat, ea,size);

  sprintf(DisaText,"%s%c.%c %s, %s",opcode[type],sign?'s':'u',Tasm[size],eat,reat);
  return 0;
}