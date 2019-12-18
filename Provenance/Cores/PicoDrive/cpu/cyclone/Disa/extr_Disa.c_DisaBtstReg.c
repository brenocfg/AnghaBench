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

__attribute__((used)) static int DisaBtstReg(int op)
{
  // Btst/Bchg/Bclr/Bset 0000nnn1 tteeeeee (nn=reg number, eeeeee=Dest ea)
  int type=0;
  int sea=0,dea=0;
  char seat[64]="",deat[64]="";
  char *opcode[4]={"btst","bchg","bclr","bset"};

  sea =(op>>9)&7;
  type=(op>>6)&3;
  dea=  op&0x3f;

  if ((dea&0x38)==0x08) return 1; // movep
  DisaGetEa(seat,sea,0);
  DisaGetEa(deat,dea,0);

  sprintf(DisaText,"%s %s, %s",opcode[type],seat,deat);
  return 0;
}