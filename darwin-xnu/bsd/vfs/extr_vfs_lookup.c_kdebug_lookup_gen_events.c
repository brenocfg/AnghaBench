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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KDBG_VFS_LOOKUP_FLAG_LOOKUP ; 
 int /*<<< orphan*/  kdebug_vfs_lookup (long*,int,void*,int /*<<< orphan*/ ) ; 

void
kdebug_lookup_gen_events(long *dbg_parms, int dbg_namelen, void *dp,
		boolean_t lookup)
{
	kdebug_vfs_lookup(dbg_parms, dbg_namelen, dp,
			lookup ? KDBG_VFS_LOOKUP_FLAG_LOOKUP : 0);
}