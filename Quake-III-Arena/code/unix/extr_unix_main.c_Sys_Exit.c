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
 int /*<<< orphan*/  Sys_ConsoleInputShutdown () ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 

void Sys_Exit( int ex ) {
  Sys_ConsoleInputShutdown();

#ifdef NDEBUG // regular behavior

  // We can't do this 
  //  as long as GL DLL's keep installing with atexit...
  //exit(ex);
  _exit(ex);
#else

  // Give me a backtrace on error exits.
  assert( ex == 0 );
  exit(ex);
#endif
}