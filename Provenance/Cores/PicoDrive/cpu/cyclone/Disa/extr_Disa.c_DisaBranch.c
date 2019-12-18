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
 int DisaLong (int) ; 
 int DisaPc ; 
 int /*<<< orphan*/  DisaText ; 
 scalar_t__ DisaWord (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int DisaBranch(int op)
{
  // Branch 0110cccc nn  (cccc=condition)
  int pc=0,Offset=0;

  static char *BraCode[16]=
  {"bra","bsr","bhi","bls","bcc","bcs","bne","beq",
   "bvc","bvs","bpl","bmi","bge","blt","bgt","ble"};
  char *Bra="";

  // Get condition code
  Bra=BraCode[(op>>8)&0x0f];

  // Get offset
  pc=DisaPc;
  Offset=(char)(op&0xff);
       if (Offset== 0) { Offset=(short)DisaWord(DisaPc); DisaPc+=2; }
  else if (Offset==-1) { Offset=       DisaLong(DisaPc); DisaPc+=4; }

  sprintf(DisaText,"%s %x",Bra,pc+Offset);
  return 0;
}