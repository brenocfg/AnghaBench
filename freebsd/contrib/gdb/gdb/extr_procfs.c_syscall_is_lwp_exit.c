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
 int SYS_lwp_exit ; 
 int SYS_lwpexit ; 

__attribute__((used)) static int
syscall_is_lwp_exit (procinfo *pi, int scall)
{

#ifdef SYS_lwp_exit
  if (scall == SYS_lwp_exit)
    return 1;
#endif
#ifdef SYS_lwpexit
  if (scall == SYS_lwpexit)
    return 1;
#endif
  return 0;
}