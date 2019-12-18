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
struct pex_time {int dummy; } ;
struct pex_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int errno ; 
 int /*<<< orphan*/  kill (long,int /*<<< orphan*/ ) ; 
 scalar_t__ pex_wait (struct pex_obj*,long,int*,struct pex_time*) ; 

__attribute__((used)) static int
pex_unix_wait (struct pex_obj *obj, long pid, int *status,
	       struct pex_time *time, int done, const char **errmsg,
	       int *err)
{
  /* If we are cleaning up when the caller didn't retrieve process
     status for some reason, encourage the process to go away.  */
  if (done)
    kill (pid, SIGTERM);

  if (pex_wait (obj, pid, status, time) < 0)
    {
      *err = errno;
      *errmsg = "wait";
      return -1;
    }

  return 0;
}