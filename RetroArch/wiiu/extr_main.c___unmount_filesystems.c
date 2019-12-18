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
 int /*<<< orphan*/  fatUnmount (char*) ; 
 scalar_t__ iosuhaxMount ; 
 int /*<<< orphan*/  unmount_sd_fat (char*) ; 

__attribute__((weak))
void __unmount_filesystems(void)
{
#ifdef HAVE_LIBFAT
   if (iosuhaxMount)
   {
      fatUnmount("sd:");
      fatUnmount("usb:");
   }
   else
      unmount_sd_fat("sd");
#else
   unmount_sd_fat("sd");
#endif
}