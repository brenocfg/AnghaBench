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
 void* ALLOC_REG_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NOT_A_BARRIER ; 
 int /*<<< orphan*/  reg_obstack ; 
 int /*<<< orphan*/  reg_pending_barrier ; 
 void* reg_pending_clobbers ; 
 void* reg_pending_sets ; 
 void* reg_pending_uses ; 

void
init_deps_global (void)
{
  reg_pending_sets = ALLOC_REG_SET (&reg_obstack);
  reg_pending_clobbers = ALLOC_REG_SET (&reg_obstack);
  reg_pending_uses = ALLOC_REG_SET (&reg_obstack);
  reg_pending_barrier = NOT_A_BARRIER;
}