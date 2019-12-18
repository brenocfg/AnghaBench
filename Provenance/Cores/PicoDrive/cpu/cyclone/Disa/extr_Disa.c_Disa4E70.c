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
 int /*<<< orphan*/  DisaText ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int Disa4E70(int op)
{
  char *inst[8]={"reset","nop","stop","rte","rtd","rts","trapv","rtr"};
  int n=0;

  n=op&7;

  sprintf(DisaText,"%s",inst[n]);

  //todo - 'stop' with 16 bit data
  
  return 0;
}