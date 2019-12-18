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
struct nfs_server {int flags; } ;
struct nfs_fsinfo {int dummy; } ;
struct nfs_fh {int dummy; } ;

/* Variables and functions */
 int NFS4ERR_WRONGSEC ; 
 int NFS_MOUNT_SECFLAVOUR ; 
 int nfs4_do_fsinfo (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 
 int nfs4_find_root_sec (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 
 int nfs4_lookup_root (struct nfs_server*,struct nfs_fh*,struct nfs_fsinfo*) ; 
 int nfs4_map_errors (int) ; 
 int nfs4_server_capabilities (struct nfs_server*,struct nfs_fh*) ; 

__attribute__((used)) static int nfs4_proc_get_root(struct nfs_server *server, struct nfs_fh *fhandle,
			      struct nfs_fsinfo *info)
{
	int status = nfs4_lookup_root(server, fhandle, info);
	if ((status == -NFS4ERR_WRONGSEC) && !(server->flags & NFS_MOUNT_SECFLAVOUR))
		/*
		 * A status of -NFS4ERR_WRONGSEC will be mapped to -EPERM
		 * by nfs4_map_errors() as this function exits.
		 */
		status = nfs4_find_root_sec(server, fhandle, info);
	if (status == 0)
		status = nfs4_server_capabilities(server, fhandle);
	if (status == 0)
		status = nfs4_do_fsinfo(server, fhandle, info);
	return nfs4_map_errors(status);
}