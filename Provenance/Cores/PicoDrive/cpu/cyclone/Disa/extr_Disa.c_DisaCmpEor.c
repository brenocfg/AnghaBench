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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 

__attribute__((used)) static int DisaCmpEor(int op)
{
  // Cmp/Eor 1011rrrt xxeeeeee (rrr=Dn, t=cmp/eor, xx=size extension, eeeeee=ea)
  char reat[64]="",eat[64]="";
  int type=0,size=0;

  type=(op>>8)&1;
  size=(op>>6)&3; if (size>=3) return 1; // cmpa opcode
  if ((op&0xf138)==0xb108) return 1; // cmpm opcode

  DisaGetEa(reat,(op>>9)&7,size);
  DisaGetEa(eat,  op&0x3f, size);

  if (type) sprintf(DisaText,"eor.%c %s, %s",Tasm[size],reat,eat);
  else      sprintf(DisaText,"cmp.%c %s, %s",Tasm[size],eat,reat);
  return 0;
}