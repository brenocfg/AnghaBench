#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ zc_history; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 char* cmdstr ; 
 int ioctl (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  zfsdevfd ; 

__attribute__((used)) static int
ioctl_with_cmdstr(int ioc, zfs_cmd_t *zc)
{
	int err;

	if (cmdstr[0])
		zc->zc_history = (uint64_t)(uintptr_t)cmdstr;
	err = ioctl(zfsdevfd, ioc, zc);
	cmdstr[0] = '\0';
	return (err);
}