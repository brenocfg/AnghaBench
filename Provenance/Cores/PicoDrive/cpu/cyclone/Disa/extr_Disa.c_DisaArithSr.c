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

__attribute__((used)) static int DisaArithSr(int op)
{
  // Ori/Andi/Eori $nnnn,sr 0000t0tx 0s111100
  char *opcode[6]={"ori","andi","","","","eori"};
  char seat[64]="";
  int type=0,size=0;

  type=(op>>9)&5;
  size=(op>>6)&1;

  DisaGetEa(seat,0x3c,size);
  sprintf(DisaText,"%s.%c %s, %s", opcode[type], Tasm[size], seat, size?"sr":"ccr");

  return 0;
}