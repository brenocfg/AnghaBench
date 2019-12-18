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
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ diffpid ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tmpname ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 

__attribute__((used)) static void
cleanup (int signo __attribute__((unused)))
{
#if HAVE_WORKING_FORK || HAVE_WORKING_VFORK
  if (0 < diffpid)
    kill (diffpid, SIGPIPE);
#endif
  if (tmpname)
    unlink (tmpname);
}