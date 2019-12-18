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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 scalar_t__ Run ; 
 int SIGHUP ; 
 scalar_t__ amd_state ; 
 int /*<<< orphan*/  dlog (char*) ; 
 scalar_t__ do_mapc_reload ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/  (*) (int)) ; 

__attribute__((used)) static RETSIGTYPE
sighup(int sig)
{
#ifdef REINSTALL_SIGNAL_HANDLER
  signal(sig, sighup);
#endif /* REINSTALL_SIGNAL_HANDLER */

  if (sig != SIGHUP)
    dlog("spurious call to sighup");
  /*
   * Force a reload by zero'ing the timer
   */
  if (amd_state == Run)
    do_mapc_reload = 0;
}