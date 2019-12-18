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
 int __ps2_release_descriptor (int) ; 
 int fileXioDclose (int) ; 
 scalar_t__ is_fd_valid (int) ; 

int ps2fileXioDclose(int fd)
{
   int ret = -19;
   if (is_fd_valid(fd)) {
      ret = __ps2_release_descriptor(fd);
   } else if (fd > 0) {
      ret = fileXioDclose(fd);
   }

   return ret;
}