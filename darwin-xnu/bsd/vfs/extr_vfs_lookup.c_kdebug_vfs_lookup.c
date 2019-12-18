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
typedef  int uint32_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KDBG_RELEASE (int,long,long,long,long) ; 
 int /*<<< orphan*/  KDBG_RELEASE_NOPROCFILT (int,long,long,long,long) ; 
 int KDBG_VFS_LOOKUP_FLAG_LOOKUP ; 
 int KDBG_VFS_LOOKUP_FLAG_NOPROCFILT ; 
 int VFS_LOOKUP ; 
 int VFS_LOOKUP_DONE ; 
 long kdebug_vnode (void*) ; 

void
kdebug_vfs_lookup(long *dbg_parms, int dbg_namelen, void *dp, uint32_t flags)
{
	int code;
	unsigned int i;
	bool lookup = flags & KDBG_VFS_LOOKUP_FLAG_LOOKUP;
	bool noprocfilt = flags & KDBG_VFS_LOOKUP_FLAG_NOPROCFILT;

	/*
	 * In the event that we collect multiple, consecutive pathname
	 * entries, we must mark the start of the path's string and the end.
	 */
	if (lookup) {
		code = VFS_LOOKUP | DBG_FUNC_START;
	} else {
		code = VFS_LOOKUP_DONE | DBG_FUNC_START;
	}

	if (dbg_namelen <= (int)(3 * sizeof(long)))
		code |= DBG_FUNC_END;

	if (noprocfilt) {
		KDBG_RELEASE_NOPROCFILT(code, kdebug_vnode(dp), dbg_parms[0],
				dbg_parms[1], dbg_parms[2]);
	} else {
		KDBG_RELEASE(code, kdebug_vnode(dp), dbg_parms[0], dbg_parms[1],
				dbg_parms[2]);
	}

	code &= ~DBG_FUNC_START;

	for (i=3, dbg_namelen -= (3 * sizeof(long)); dbg_namelen > 0; i+=4, dbg_namelen -= (4 * sizeof(long))) {
		if (dbg_namelen <= (int)(4 * sizeof(long)))
			code |= DBG_FUNC_END;

		if (noprocfilt) {
			KDBG_RELEASE_NOPROCFILT(code, dbg_parms[i], dbg_parms[i + 1],
					dbg_parms[i + 2], dbg_parms[i + 3]);
		} else {
			KDBG_RELEASE(code, dbg_parms[i], dbg_parms[i + 1], dbg_parms[i + 2],
					dbg_parms[i + 3]);
		}
	}
}