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

__attribute__((used)) static int DisaCmpm(int op)
{
  // Cmpm  1011ddd1 xx001sss
  int size=0,dea=0,sea=0;
  char deat[64]="",seat[64]="";

  dea =(op>> 9)&7; dea|=8;
  size=(op>> 6)&3; if (size>=3) return 1;
  sea  = op&0x3f;

  DisaGetEa(deat,dea,size);
  DisaGetEa(seat,sea,size);

  sprintf(DisaText,"cmpm.%c (%s)+, (%s)+",Tasm[size],seat,deat);

  return 0;
}