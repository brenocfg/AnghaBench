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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SNAPSHOT_OP_CREATE ; 
 int __fs_snapshot (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
fs_snapshot_create(int dirfd, const char *name, uint32_t flags)
{
	return __fs_snapshot(SNAPSHOT_OP_CREATE, dirfd, name, NULL, NULL, flags);
}