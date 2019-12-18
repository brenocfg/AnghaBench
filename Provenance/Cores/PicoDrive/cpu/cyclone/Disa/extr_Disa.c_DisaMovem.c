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
 int DisaPc ; 
 int /*<<< orphan*/  DisaText ; 
 int DisaWord (int) ; 
 int /*<<< orphan*/  MakeRegList (char*,int,int) ; 
 int* Tasm ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 

__attribute__((used)) static int DisaMovem(int op)
{
  // Movem 01001d00 1xeeeeee regmask  d=direction, x=size, eeeeee=EA
  int dir=0,size=0;
  int ea=0,mask=0;
  char list[64]="",eat[64]="";

  dir=(op>>10)&1;
  size=((op>>6)&1)+1;
  ea=op&0x3f; if (ea<0x10) return 1; // ext opcode

  mask=DisaWord(DisaPc)&0xffff; DisaPc+=2;

  MakeRegList(list,mask,ea); // Turn register mask into text
  DisaGetEa(eat,ea,size);

  if (dir) sprintf(DisaText,"movem.%c %s, %s",Tasm[size],eat,list);
  else     sprintf(DisaText,"movem.%c %s, %s",Tasm[size],list,eat);
  return 0;
}