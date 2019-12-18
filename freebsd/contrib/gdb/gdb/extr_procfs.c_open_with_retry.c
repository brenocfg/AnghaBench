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
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static int
open_with_retry (const char *pathname, int flags)
{
  int retries_remaining, status;

  retries_remaining = 2;

  while (1)
    {
      status = open (pathname, flags);

      if (status >= 0 || retries_remaining == 0)
	break;
      else if (errno != EINTR && errno != EAGAIN)
	{
	  retries_remaining--;
	  sleep (1);
	}
    }

  return status;
}