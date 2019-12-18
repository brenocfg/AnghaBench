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
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minipool_obstack ; 
 char* minipool_startobj ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_add_gc_roots (void)
{
  gcc_obstack_init(&minipool_obstack);
  minipool_startobj = (char *) obstack_alloc (&minipool_obstack, 0);
}