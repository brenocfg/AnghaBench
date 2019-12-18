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
typedef  int /*<<< orphan*/  tree ;
struct tlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ save_expr_cache ; 
 char* tlist_firstobj ; 
 int /*<<< orphan*/  tlist_obstack ; 
 int /*<<< orphan*/  verify_tree (int /*<<< orphan*/ ,struct tlist**,struct tlist**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn_for_collisions (struct tlist*) ; 
 scalar_t__ warned_ids ; 

void
verify_sequence_points (tree expr)
{
  struct tlist *before_sp = 0, *after_sp = 0;

  warned_ids = 0;
  save_expr_cache = 0;
  if (tlist_firstobj == 0)
    {
      gcc_obstack_init (&tlist_obstack);
      tlist_firstobj = (char *) obstack_alloc (&tlist_obstack, 0);
    }

  verify_tree (expr, &before_sp, &after_sp, 0);
  warn_for_collisions (after_sp);
  obstack_free (&tlist_obstack, tlist_firstobj);
}