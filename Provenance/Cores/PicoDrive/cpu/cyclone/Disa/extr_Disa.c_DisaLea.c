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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int DisaLea(int op)
{
  // Lea 0100nnn1 11eeeeee (eeeeee=ea)
  int sea=0,dea=0;
  char seat[64]="",deat[64]="";

  sea=op&0x003f;
  DisaGetEa(seat,sea,0);

  dea=(op>>9)&7; dea|=8;
  DisaGetEa(deat,dea,2);

  sprintf(DisaText,"lea %s, %s",seat,deat);
  return 0;
}