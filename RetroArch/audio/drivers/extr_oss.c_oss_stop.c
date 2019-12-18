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
 int /*<<< orphan*/  SNDCTL_DSP_RESET ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int oss_is_paused ; 

__attribute__((used)) static bool oss_stop(void *data)
{
   int *fd = (int*)data;

   if (ioctl(*fd, SNDCTL_DSP_RESET, 0) < 0)
      return false;

   oss_is_paused = true;
   return true;
}