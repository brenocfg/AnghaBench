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
 scalar_t__ CP_DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ current_namespace ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ global_namespace ; 
 int /*<<< orphan*/  leave_scope () ; 

void
pop_namespace (void)
{
  gcc_assert (current_namespace != global_namespace);
  current_namespace = CP_DECL_CONTEXT (current_namespace);
  /* The binding level is not popped, as it might be re-opened later.  */
  leave_scope ();
}