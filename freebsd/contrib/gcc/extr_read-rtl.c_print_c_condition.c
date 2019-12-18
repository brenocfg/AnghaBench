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
 scalar_t__ htab_find (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  joined_conditions ; 
 int /*<<< orphan*/  print_rtx_ptr_loc (char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
print_c_condition (const char *cond)
{
  const char **halves = (const char **) htab_find (joined_conditions, &cond);
  if (halves != 0)
    {
      printf ("(");
      print_c_condition (halves[1]);
      printf (" && ");
      print_c_condition (halves[2]);
      printf (")");
    }
  else
    {
      putc ('\n', stdout);
      print_rtx_ptr_loc (cond);
      printf ("(%s)", cond);
    }
}