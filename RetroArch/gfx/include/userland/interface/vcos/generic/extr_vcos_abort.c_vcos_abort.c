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
 int /*<<< orphan*/  VCOS_ALERT (char*) ; 
 int /*<<< orphan*/  _bkpt () ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  vclib_cache_flush () ; 
 int /*<<< orphan*/  vcos_backtrace_self () ; 

void vcos_abort(void)
{
   VCOS_ALERT("vcos_abort: Halting");

#ifdef __VIDEOCORE__
   _bkpt();
#endif

#if defined(VCOS_HAVE_BACKTRACE) && !defined(NDEBUG)
   vcos_backtrace_self();
#endif

#ifdef __VIDEOCORE__
   /* Flush the cache to help with postmortem RAM-dump debugging */
   vclib_cache_flush();
#endif

#ifdef PLATFORM_RASPBERRYPI
   extern void pattern(int);
   while(1)
      pattern(8);
#endif

   /* Insert chosen fatal error handler here */
#if defined __VIDEOCORE__ && !defined(NDEBUG)
   while(1); /* allow us to attach a debugger after the fact and see where we came from. */
#else
   abort(); /* on vc this ends up in _exit_halt which doesn't give us any stack backtrace */
#endif
}