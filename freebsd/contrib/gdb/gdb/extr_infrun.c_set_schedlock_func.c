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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 scalar_t__ cmd_type (struct cmd_list_element*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedlock_off ; 
 int /*<<< orphan*/  scheduler_mode ; 
 scalar_t__ set_cmd ; 
 int /*<<< orphan*/  target_can_lock_scheduler ; 
 int /*<<< orphan*/  target_shortname ; 

__attribute__((used)) static void
set_schedlock_func (char *args, int from_tty, struct cmd_list_element *c)
{
  /* NOTE: cagney/2002-03-17: The add_show_from_set() function clones
     the set command passed as a parameter.  The clone operation will
     include (BUG?) any ``set'' command callback, if present.
     Commands like ``info set'' call all the ``show'' command
     callbacks.  Unfortunately, for ``show'' commands cloned from
     ``set'', this includes callbacks belonging to ``set'' commands.
     Making this worse, this only occures if add_show_from_set() is
     called after add_cmd_sfunc() (BUG?).  */
  if (cmd_type (c) == set_cmd)
    if (!target_can_lock_scheduler)
      {
	scheduler_mode = schedlock_off;
	error ("Target '%s' cannot support this command.", target_shortname);
      }
}