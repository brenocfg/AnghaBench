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
typedef  int /*<<< orphan*/  ver ;

/* Variables and functions */
 int /*<<< orphan*/  sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_zfs_spa_version(void)
{
	size_t ver_size;
	int ver = 0;

	ver_size = sizeof(ver);
	sysctlbyname("vfs.zfs.version.spa", &ver, &ver_size, NULL, 0);

	return (ver);
}