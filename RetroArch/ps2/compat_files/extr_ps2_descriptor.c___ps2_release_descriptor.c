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
 int MAX_OPEN_FILES ; 
 scalar_t__ __ps2_fd_drop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** __ps2_fdmap ; 
 int /*<<< orphan*/  _lock () ; 
 int /*<<< orphan*/  _unlock () ; 
 scalar_t__ is_fd_valid (int) ; 

int __ps2_release_descriptor(int fd)
{
   int res = -1;

   if (is_fd_valid(fd) && __ps2_fd_drop(__ps2_fdmap[MAX_OPEN_FILES - fd]) >= 0)
   {
      _lock();
      /* Correct fd value */
      fd = MAX_OPEN_FILES - fd;
      __ps2_fdmap[fd] = NULL;
      res = 0;
      _unlock();
   }

   return res;
}