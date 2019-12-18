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

/* Variables and functions */
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
print_mention_exception_catchpoint (struct breakpoint *b)
{
  if (strstr (b->addr_string, "throw") != NULL)
    printf_filtered ("Catchpoint %d (throw)", b->number);
  else
    printf_filtered ("Catchpoint %d (catch)", b->number);
}