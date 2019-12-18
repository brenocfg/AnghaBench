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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int DisaMoveSr(int op)
{
  // 01000tt0 11eeeeee (tt=type, xx=size, eeeeee=EA)
  int type=0,ea=0;
  char eat[64]="";

  type=(op>>9)&3;
  ea=op&0x3f;
  DisaGetEa(eat,ea,1);

  switch (type)
  {
    default: sprintf(DisaText,"move sr, %s", eat); break;
    case 1:  sprintf(DisaText,"move ccr, %s",eat); break;
    case 2:  sprintf(DisaText,"move %s, ccr",eat); break;
    case 3:  sprintf(DisaText,"move %s, sr", eat); break;
  }
  return 0;
}