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
struct field {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  recursive_dump_type (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_arg_types (struct field *args, int nargs, int spaces)
{
  if (args != NULL)
    {
      int i;

      for (i = 0; i < nargs; i++)
	recursive_dump_type (args[i].type, spaces + 2);
    }
}