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
 int /*<<< orphan*/  MADV_PROTECT ; 
 int MCL_CURRENT ; 
 int MCL_FUTURE ; 
 int /*<<< orphan*/  PROCLOCK ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  madvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlockall (int) ; 
 scalar_t__ plock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
do_memory_locking(void)
{
#if defined(HAVE_PLOCK) || defined(HAVE_MLOCKALL)
  int locked_ok = 0;
#else /* not HAVE_PLOCK and not HAVE_MLOCKALL */
  plog(XLOG_WARNING, "Process memory locking not supported by the OS");
#endif /* not HAVE_PLOCK and not HAVE_MLOCKALL */
#ifdef HAVE_PLOCK
# ifdef _AIX
  /*
   * On AIX you must lower the stack size using ulimit() before calling
   * plock.  Otherwise plock will reserve a lot of memory space based on
   * your maximum stack size limit.  Since it is not easily possible to
   * tell what should the limit be, I print a warning before calling
   * plock().  See the manual pages for ulimit(1,3,4) on your AIX system.
   */
  plog(XLOG_WARNING, "AIX: may need to lower stack size using ulimit(3) before calling plock");
# endif /* _AIX */
  if (!locked_ok && plock(PROCLOCK) != 0)
    plog(XLOG_WARNING, "Couldn't lock process pages in memory using plock(): %m");
  else
    locked_ok = 1;
#endif /* HAVE_PLOCK */
#ifdef HAVE_MLOCKALL
  if (!locked_ok && mlockall(MCL_CURRENT|MCL_FUTURE) != 0)
    plog(XLOG_WARNING, "Couldn't lock process pages in memory using mlockall(): %m");
  else
    locked_ok = 1;
#endif /* HAVE_MLOCKALL */
#if defined(HAVE_PLOCK) || defined(HAVE_MLOCKALL)
  if (locked_ok)
    plog(XLOG_INFO, "Locked process pages in memory");
#endif /* HAVE_PLOCK || HAVE_MLOCKALL */

#if defined(HAVE_MADVISE) && defined(MADV_PROTECT)
    madvise(NULL, 0, MADV_PROTECT); /* may be redundant of the above worked out */
#endif /* defined(HAVE_MADVISE) && defined(MADV_PROTECT) */
}