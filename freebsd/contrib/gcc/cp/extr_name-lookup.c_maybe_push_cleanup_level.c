#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ more_cleanups_ok; int /*<<< orphan*/  statement_list; } ;

/* Variables and functions */
 scalar_t__ TYPE_HAS_NONTRIVIAL_DESTRUCTOR (scalar_t__) ; 
 int /*<<< orphan*/  begin_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* current_binding_level ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  push_stmt_list () ; 
 int /*<<< orphan*/  sk_cleanup ; 

void
maybe_push_cleanup_level (tree type)
{
  if (type != error_mark_node
      && TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type)
      && current_binding_level->more_cleanups_ok == 0)
    {
      begin_scope (sk_cleanup, NULL);
      current_binding_level->statement_list = push_stmt_list ();
    }
}