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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOLIB_CREATE_INFERIOR_HOOK (int /*<<< orphan*/ ) ; 
 scalar_t__ exec_bfd ; 

__attribute__((used)) static void
procfs_post_attach (pid_t pid)
{
#ifdef SOLIB_CREATE_INFERIOR_HOOK
  if (exec_bfd)
    SOLIB_CREATE_INFERIOR_HOOK (pid);
#endif
}