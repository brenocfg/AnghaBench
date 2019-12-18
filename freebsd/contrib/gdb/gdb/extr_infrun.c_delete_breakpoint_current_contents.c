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
struct breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_breakpoint (struct breakpoint*) ; 

__attribute__((used)) static void
delete_breakpoint_current_contents (void *arg)
{
  struct breakpoint **breakpointp = (struct breakpoint **) arg;
  if (*breakpointp != NULL)
    {
      delete_breakpoint (*breakpointp);
      *breakpointp = NULL;
    }
}