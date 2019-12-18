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
 int COND_EXEC ; 
 int EXPR_LIST ; 
 int INSN_LIST ; 
 int NUM_RTX_CODE ; 
 int SET ; 
 char** rtx_format ; 
 int* rtx_next_new ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
gen_rtx_next (void)
{
  int i;
  for (i = 0; i < NUM_RTX_CODE; i++)
    {
      int k;

      rtx_next_new[i] = -1;
      if (strncmp (rtx_format[i], "iuu", 3) == 0)
	rtx_next_new[i] = 2;
      else if (i == COND_EXEC || i == SET || i == EXPR_LIST || i == INSN_LIST)
	rtx_next_new[i] = 1;
      else
	for (k = strlen (rtx_format[i]) - 1; k >= 0; k--)
	  if (rtx_format[i][k] == 'e' || rtx_format[i][k] == 'u')
	    rtx_next_new[i] = k;
    }
}