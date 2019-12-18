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
 scalar_t__ DisaWord (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,int) ; 

__attribute__((used)) static int DisaDbra(int op)
{
  // 0101cccc 11001nnn offset  (dbra/dbxx Rn,offset)
  int dea=0; char deat[64]="";
  int pc=0,Offset=0;

  static char *BraCode[16]=
  {"bt" ,"bra","bhi","bls","bcc","bcs","bne","beq",
   "bvc","bvs","bpl","bmi","bge","blt","bgt","ble"};
  char *Bra="";

  dea=op&7;
  DisaGetEa(deat,dea,2);

  // Get condition code
  Bra=BraCode[(op>>8)&0xf];

  // Get offset
  pc=DisaPc;
  Offset=(short)DisaWord(DisaPc); DisaPc+=2;

  sprintf(DisaText,"d%s %s, %x",Bra,deat,pc+Offset);
  return 0;
}