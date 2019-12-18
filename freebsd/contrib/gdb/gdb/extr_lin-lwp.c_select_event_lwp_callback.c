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
struct lwp_info {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ SIGTRAP ; 
 scalar_t__ WIFSTOPPED (scalar_t__) ; 
 scalar_t__ WSTOPSIG (scalar_t__) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
select_event_lwp_callback (struct lwp_info *lp, void *data)
{
  int *selector = data;

  gdb_assert (selector != NULL);

  /* Select only LWPs that have a SIGTRAP event pending. */
  if (lp->status != 0
      && WIFSTOPPED (lp->status) && WSTOPSIG (lp->status) == SIGTRAP)
    if ((*selector)-- == 0)
      return 1;

  return 0;
}