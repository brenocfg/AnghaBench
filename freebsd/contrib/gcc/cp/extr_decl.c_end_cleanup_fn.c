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
 int /*<<< orphan*/  expand_or_defer_fn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_from_top_level () ; 

__attribute__((used)) static void
end_cleanup_fn (void)
{
  expand_or_defer_fn (finish_function (0));

  pop_from_top_level ();
}