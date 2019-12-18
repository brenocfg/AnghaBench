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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int DisaSet(int op)
{
  // 0101cccc 11eeeeee (sxx ea)
  static char *cond[16]=
  {"t" ,"f", "hi","ls","cc","cs","ne","eq",
   "vc","vs","pl","mi","ge","lt","gt","le"};
  char *cc="";
  int ea=0;
  char eat[64]="";

  cc=cond[(op>>8)&0xf]; // Get condition code
  ea=op&0x3f;
  if ((ea&0x38)==0x08) return 1; // dbra, not scc

  DisaGetEa(eat,ea,0);
  sprintf(DisaText,"s%s %s",cc,eat);
  return 0;
}