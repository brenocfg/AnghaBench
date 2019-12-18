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
 int get_entry_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_self_id () ; 

int
get_current_task (void)
{
  int result;

  /* FIXME: language_ada should be defined in defs.h */
  /*  if (current_language->la_language != language_ada) return -1; */

  result = get_entry_number (get_self_id ());

  /* return -1 if not found */
  return result == 0 ? -1 : result;
}