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

__attribute__((used)) static int DisaAritha(int op)
{
  // Suba/Cmpa/Adda 1tt1nnnx 11eeeeee (tt=type, x=size, eeeeee=Source EA)
  int type=0,size=0,sea=0,dea=0;
  char seat[64]="",deat[64]="";
  char *aritha[4]={"suba","cmpa","adda",""};

  type=(op>>13)&3; if (type>=3) return 1;
  size=(op>>8)&1; size++;
  dea =(op>>9)&7; dea|=8; // Dest=An
  sea = op&0x003f; // Source

  DisaGetEa(seat,sea,size);
  DisaGetEa(deat,dea,size);

  sprintf(DisaText,"%s.%c %s, %s",aritha[type],Tasm[size],seat,deat);
  return 0;
}