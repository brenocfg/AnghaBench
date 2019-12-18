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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int,char*) ; 

__attribute__((used)) static int DisaMoveq(int op)
{
  // Moveq 0111rrr0 nn (rrr=Dest register, nn=data)

  int dea=0; char deat[64]="";
  char *inst="moveq";
  int val=0;

  dea=(op>>9)&7;
  DisaGetEa(deat,dea,2);

  val=(char)(op&0xff);
  sprintf(DisaText,"%s #$%x, %s",inst,val,deat);
  return 0;
}