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
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int masterpid ; 
 int serverpid ; 

void
hlfsd_going_down(int rc)
{
  int mypid = getpid();		/* XXX: should this be the global am_mypid */

  if (mypid == masterpid)
    cleanup(0);
  else if (mypid == serverpid)
    kill(masterpid, SIGTERM);

  exit(rc);
}