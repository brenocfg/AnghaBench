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
struct using_direct {int /*<<< orphan*/  outer; int /*<<< orphan*/  inner; struct using_direct* next; } ;

/* Variables and functions */
 struct using_direct* cp_add_using (char const*,unsigned int,unsigned int,struct using_direct*) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 struct using_direct* using_list ; 

void
cp_add_using_directive (const char *name, unsigned int outer_length,
			unsigned int inner_length)
{
  struct using_direct *current;
  struct using_direct *new;

  /* Has it already been added?  */

  for (current = using_list; current != NULL; current = current->next)
    {
      if ((strncmp (current->inner, name, inner_length) == 0)
	  && (strlen (current->inner) == inner_length)
	  && (strlen (current->outer) == outer_length))
	return;
    }

  using_list = cp_add_using (name, inner_length, outer_length,
			     using_list);
}