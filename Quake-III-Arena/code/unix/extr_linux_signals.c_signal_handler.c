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
 int /*<<< orphan*/  GLimp_Shutdown () ; 
 int /*<<< orphan*/  Sys_Exit (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ qtrue ; 
 scalar_t__ signalcaught ; 

__attribute__((used)) static void signal_handler(int sig) // bk010104 - replace this... (NOTE TTimo huh?)
{
  if (signalcaught)
  {
    printf("DOUBLE SIGNAL FAULT: Received signal %d, exiting...\n", sig);
    Sys_Exit(1); // bk010104 - abstraction
  }

  signalcaught = qtrue;
  printf("Received signal %d, exiting...\n", sig);
#ifndef DEDICATED
  GLimp_Shutdown(); // bk010104 - shouldn't this be CL_Shutdown
#endif
  Sys_Exit(0); // bk010104 - abstraction NOTE TTimo send a 0 to avoid DOUBLE SIGNAL FAULT
}