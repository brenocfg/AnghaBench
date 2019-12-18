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
 int /*<<< orphan*/  extract_packages (char*) ; 
 scalar_t__ my_system (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null ; 

__attribute__((used)) static void
install_nfs(void)
{
    if (my_system("ifconfig eth0 134.96.81.36 netmask 255.255.255.224 "
		  "broadcast 134.96.81.63 %s", null))
	return;
    if (my_system("route add -net 134.96.81.32 %s", null))
	return;
    if (my_system("mount -t nfs 134.96.81.38:"
		  "/local/ftp/pub/linux/ELF.binary/tar /source %s", null))
	return;
    extract_packages("/base");
    if (my_system("umount /source %s", null))
	return;
    if (my_system("ifconfig eth0 down %s", null))
	return;
}