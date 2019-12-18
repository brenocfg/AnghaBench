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
 int /*<<< orphan*/  xbox_io_mount (char*,char*) ; 

__attribute__((used)) static void frontend_xdk_init(void *data)
{
   (void)data;
#if defined(_XBOX1) && !defined(IS_SALAMANDER)
   /* Mount drives */
   xbox_io_mount("A:", "cdrom0");
   xbox_io_mount("C:", "Harddisk0\\Partition0");
   xbox_io_mount("E:", "Harddisk0\\Partition1");
   xbox_io_mount("Z:", "Harddisk0\\Partition2");
   xbox_io_mount("F:", "Harddisk0\\Partition6");
   xbox_io_mount("G:", "Harddisk0\\Partition7");
#endif
}