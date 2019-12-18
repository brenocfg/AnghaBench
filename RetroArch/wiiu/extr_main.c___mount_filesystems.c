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
 int /*<<< orphan*/  fatInitDefault () ; 
 scalar_t__ iosuhaxMount ; 
 int /*<<< orphan*/  mount_sd_fat (char*) ; 

__attribute__((weak))
void __mount_filesystems(void)
{
#ifdef HAVE_LIBFAT
   if(iosuhaxMount)
      fatInitDefault();
   else
      mount_sd_fat("sd");
#else
   mount_sd_fat("sd");
#endif
}