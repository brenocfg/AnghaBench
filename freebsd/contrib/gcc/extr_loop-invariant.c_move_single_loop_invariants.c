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

/* Variables and functions */
 int /*<<< orphan*/  find_invariants (struct loop*) ; 
 int /*<<< orphan*/  find_invariants_to_move () ; 
 int /*<<< orphan*/  free_inv_motion_data () ; 
 int /*<<< orphan*/  init_inv_motion_data () ; 
 int /*<<< orphan*/  move_invariants (struct loop*) ; 

__attribute__((used)) static void
move_single_loop_invariants (struct loop *loop)
{
  init_inv_motion_data ();

  find_invariants (loop);
  find_invariants_to_move ();
  move_invariants (loop);

  free_inv_motion_data ();
}