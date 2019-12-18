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

__attribute__((used)) static int DisaArithImm(int op)
{
  // Or/And/Sub/Add/Eor/Cmp Immediate 0000ttt0 xxDDDddd (tt=type, xx=size extension, DDDddd=Dest ea)
  int dea=0;
  char seat[64]="",deat[64]="";
  int type=0,size=0;
  char *arith[8]={"or","and","sub","add","?","eor","cmp","?"};

  type=(op>>9)&7; if (type==4 || type>=7) return 1;
  size=(op>>6)&3; if (size>=3) return 1;
  dea=op&0x3f; if (dea==0x3c) return 1;

  DisaGetEa(seat,0x3c,size);
  DisaGetEa(deat,dea, size);

  sprintf(DisaText,"%si.%c %s, %s",arith[type],Tasm[size],seat,deat);
  return 0;
}