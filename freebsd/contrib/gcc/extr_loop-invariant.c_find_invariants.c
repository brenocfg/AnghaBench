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
struct loop {int dummy; } ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_always_reached (struct loop*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_defs (struct loop*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_exits (struct loop*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_invariants_body (struct loop*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_loop_body_in_dom_order (struct loop*) ; 
 int /*<<< orphan*/  merge_identical_invariants () ; 

__attribute__((used)) static void
find_invariants (struct loop *loop)
{
  bitmap may_exit = BITMAP_ALLOC (NULL);
  bitmap always_reached = BITMAP_ALLOC (NULL);
  bitmap has_exit = BITMAP_ALLOC (NULL);
  bitmap always_executed = BITMAP_ALLOC (NULL);
  basic_block *body = get_loop_body_in_dom_order (loop);

  find_exits (loop, body, may_exit, has_exit);
  compute_always_reached (loop, body, may_exit, always_reached);
  compute_always_reached (loop, body, has_exit, always_executed);

  find_defs (loop, body);
  find_invariants_body (loop, body, always_reached, always_executed);
  merge_identical_invariants ();

  BITMAP_FREE (always_reached);
  BITMAP_FREE (always_executed);
  BITMAP_FREE (may_exit);
  BITMAP_FREE (has_exit);
  free (body);
}