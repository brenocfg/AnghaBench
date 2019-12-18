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
struct breakpoint {int /*<<< orphan*/  number; int /*<<< orphan*/  addr_string; } ;
typedef  enum print_stop_action { ____Placeholder_print_stop_action } print_stop_action ;

/* Variables and functions */
 int PRINT_SRC_AND_LOC ; 
 int /*<<< orphan*/  annotate_catchpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum print_stop_action
print_exception_catchpoint (struct breakpoint *b)
{
  annotate_catchpoint (b->number);

  if (strstr (b->addr_string, "throw") != NULL)
    printf_filtered ("\nCatchpoint %d (exception thrown)\n",
		     b->number);
  else
    printf_filtered ("\nCatchpoint %d (exception caught)\n",
		     b->number);

  return PRINT_SRC_AND_LOC;
}