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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 

__attribute__((used)) static int DisaNeg(int op)
{
  // 01000tt0 xxeeeeee (tt=negx/clr/neg/not, xx=size, eeeeee=EA)
  char eat[64]="";
  int type=0,size=0;
  char *opcode[4]={"negx","clr","neg","not"};

  type=(op>>9)&3;
  size=(op>>6)&3; if (size>=3) return 1;
  DisaGetEa(eat,op&0x3f,size);

  sprintf(DisaText,"%s.%c %s",opcode[type],Tasm[size],eat);
  return 0;
}