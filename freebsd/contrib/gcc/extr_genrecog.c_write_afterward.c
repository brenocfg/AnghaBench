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
struct decision {scalar_t__ subroutine_number; int number; int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int /*<<< orphan*/  change_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 

__attribute__((used)) static void
write_afterward (struct decision *start, struct decision *afterward,
		 const char *indent)
{
  if (!afterward || start->subroutine_number > 0)
    printf("%sgoto ret0;\n", indent);
  else
    {
      change_state (start->position, afterward->position, indent);
      printf ("%sgoto L%d;\n", indent, afterward->number);
    }
}