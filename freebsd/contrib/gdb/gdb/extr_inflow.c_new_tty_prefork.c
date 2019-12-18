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
 char* inferior_thisrun_terminal ; 

void
new_tty_prefork (char *ttyname)
{
  /* Save the name for later, for determining whether we and the child
     are sharing a tty.  */
  inferior_thisrun_terminal = ttyname;
}