#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rpc_cred {int dummy; } ;
struct nfs_access_entry {int mask; int /*<<< orphan*/  jiffies; struct rpc_cred* cred; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct TYPE_2__ {scalar_t__ access_supported; int /*<<< orphan*/  access_result; } ;
struct nfs4_opendata {TYPE_1__ o_res; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int FMODE_READ ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int NFS4ERR_ACCESS ; 
 int __FMODE_EXEC ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfs4_close_state (struct nfs4_state*,int) ; 
 int /*<<< orphan*/  nfs_access_add_cache (int /*<<< orphan*/ ,struct nfs_access_entry*) ; 
 int /*<<< orphan*/  nfs_access_set_mask (struct nfs_access_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_opendata_access(struct rpc_cred *cred,
				struct nfs4_opendata *opendata,
				struct nfs4_state *state, fmode_t fmode,
				int openflags)
{
	struct nfs_access_entry cache;
	u32 mask;

	/* access call failed or for some reason the server doesn't
	 * support any access modes -- defer access call until later */
	if (opendata->o_res.access_supported == 0)
		return 0;

	mask = 0;
	/* don't check MAY_WRITE - a newly created file may not have
	 * write mode bits, but POSIX allows the creating process to write.
	 * use openflags to check for exec, because fmode won't
	 * always have FMODE_EXEC set when file open for exec. */
	if (openflags & __FMODE_EXEC) {
		/* ONLY check for exec rights */
		mask = MAY_EXEC;
	} else if (fmode & FMODE_READ)
		mask = MAY_READ;

	cache.cred = cred;
	cache.jiffies = jiffies;
	nfs_access_set_mask(&cache, opendata->o_res.access_result);
	nfs_access_add_cache(state->inode, &cache);

	if ((mask & ~cache.mask & (MAY_READ | MAY_WRITE | MAY_EXEC)) == 0)
		return 0;

	/* even though OPEN succeeded, access is denied. Close the file */
	nfs4_close_state(state, fmode);
	return -NFS4ERR_ACCESS;
}