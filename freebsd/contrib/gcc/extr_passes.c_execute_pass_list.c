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
struct tree_opt_pass {struct tree_opt_pass* next; struct tree_opt_pass* sub; } ;

/* Variables and functions */
 scalar_t__ execute_one_pass (struct tree_opt_pass*) ; 

void
execute_pass_list (struct tree_opt_pass *pass)
{
  do
    {
      if (execute_one_pass (pass) && pass->sub)
        execute_pass_list (pass->sub);
      pass = pass->next;
    }
  while (pass);
}