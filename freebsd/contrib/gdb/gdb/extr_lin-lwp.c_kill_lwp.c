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
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  __NR_tkill ; 
 scalar_t__ errno ; 
 int kill (int,int) ; 
 int syscall (int /*<<< orphan*/ ,int,int) ; 
 int tkill_failed ; 

__attribute__((used)) static int
kill_lwp (int lwpid, int signo)
{
  errno = 0;

/* Use tkill, if possible, in case we are using nptl threads.  If tkill
   fails, then we are not using nptl threads and we should be using kill.  */

#ifdef HAVE_TKILL_SYSCALL
  if (!tkill_failed)
    {
      int ret = syscall (__NR_tkill, lwpid, signo);
      if (errno != ENOSYS)
	return ret;
      errno = 0;
      tkill_failed = 1;
    }
#endif

  return kill (lwpid, signo);
}