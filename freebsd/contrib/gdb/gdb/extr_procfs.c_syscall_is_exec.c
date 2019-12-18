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
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 int SYS_exec ; 
 int SYS_execv ; 
 int SYS_execve ; 
 scalar_t__ find_syscall (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
syscall_is_exec (procinfo *pi, int scall)
{
#ifdef SYS_exec
  if (scall == SYS_exec)
    return 1;
#endif
#ifdef SYS_execv
  if (scall == SYS_execv)
    return 1;
#endif
#ifdef SYS_execve
  if (scall == SYS_execve)
    return 1;
#endif
#ifdef DYNAMIC_SYSCALLS
  if (find_syscall (pi, "_execve"))
    return 1;
  if (find_syscall (pi, "ra_execve"))
    return 1;
#endif
  return 0;
}