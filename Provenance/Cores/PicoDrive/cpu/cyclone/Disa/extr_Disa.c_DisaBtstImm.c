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
 int /*<<< orphan*/  DisaGetEa (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisaText ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static int DisaBtstImm(int op)
{
  // Btst/Bchg/Bclr/Bset 00001000 tteeeeee 00 nn (eeeeee=ea, nn=bit number)
  int type=0;
  char seat[64]="",deat[64]="";
  char *opcode[4]={"btst","bchg","bclr","bset"};

  type=(op>>6)&3;
  DisaGetEa(seat,   0x3c,0);
  DisaGetEa(deat,op&0x3f,0);

  sprintf(DisaText,"%s %s, %s",opcode[type],seat,deat);
  return 0;
}