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
 int /*<<< orphan*/  VALGRIND_PRINTF_BACKTRACE (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  exit (int) ; 
 int unix_sighandler_quit ; 

__attribute__((used)) static void frontend_unix_sighandler(int sig)
{
#ifdef VALGRIND_PRINTF_BACKTRACE
VALGRIND_PRINTF_BACKTRACE("SIGINT");
#endif
   (void)sig;
   unix_sighandler_quit++;
   if (unix_sighandler_quit == 1) {}
   if (unix_sighandler_quit == 2) exit(1);
   /* in case there's a second deadlock in a C++ destructor or something */
   if (unix_sighandler_quit >= 3) abort();
}