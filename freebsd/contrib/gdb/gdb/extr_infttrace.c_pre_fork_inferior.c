#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  child_channel; int /*<<< orphan*/  parent_channel; } ;

/* Variables and functions */
 int pipe (int /*<<< orphan*/ ) ; 
 TYPE_1__ startup_semaphore ; 
 int /*<<< orphan*/  warning (char*) ; 

void
pre_fork_inferior (void)
{
  int status;

  status = pipe (startup_semaphore.parent_channel);
  if (status < 0)
    {
      warning ("error getting parent pipe for startup semaphore");
      return;
    }

  status = pipe (startup_semaphore.child_channel);
  if (status < 0)
    {
      warning ("error getting child pipe for startup semaphore");
      return;
    }
}