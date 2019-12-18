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
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int DisaNbcd(int op)
{
  // Nbcd 01001000 00eeeeee  (eeeeee=ea)
  int ea=0;
  char eat[64]="";

  ea=op&0x003f;
  DisaGetEa(eat,ea,0);

  sprintf(DisaText,"nbcd %s",eat);
  return 0;
}