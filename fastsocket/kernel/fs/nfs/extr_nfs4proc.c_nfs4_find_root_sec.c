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
struct nfs_server {int dummy; } ;
struct nfs_fsinfo {int dummy; } ;
struct nfs_fh {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 int NFS4ERR_WRONGSEC ; 
 int /*<<< orphan*/  NFS_MAX_SECFLAVORS ; 
 int /*<<< orphan*/  RPC_AUTH_NULL ; 
 int gss_mech_list_pseudoflavors (int /*<<< orphan*/ *) ; 
 int nfs4_lookup_root_sec (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_find_root_sec(struct nfs_server *server, struct nfs_fh *fhandle,
			      struct nfs_fsinfo *info)
{
	int i, len, status = 0;
	rpc_authflavor_t flav_array[NFS_MAX_SECFLAVORS + 2];

	len = gss_mech_list_pseudoflavors(&flav_array[0]);
	flav_array[len] = RPC_AUTH_NULL;
	len += 1;

	for (i = 0; i < len; i++) {
		status = nfs4_lookup_root_sec(server, fhandle, info, flav_array[i]);
		if (status == -NFS4ERR_WRONGSEC || status == -EACCES)
			continue;
		break;
	}
	/*
	 * -EACCESS could mean that the user doesn't have correct permissions
	 * to access the mount.  It could also mean that we tried to mount
	 * with a gss auth flavor, but rpc.gssd isn't running.  Either way,
	 * existing mount programs don't handle -EACCES very well so it should
	 * be mapped to -EPERM instead.
	 */
	if (status == -EACCES)
		status = -EPERM;
	return status;
}