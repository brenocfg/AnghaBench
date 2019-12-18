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
struct rpc_message {struct nfs2_fsstat* rpc_resp; struct nfs_fh* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; } ;
struct nfs_fsinfo {int maxfilesize; scalar_t__ lease_time; int /*<<< orphan*/  dtpref; int /*<<< orphan*/  wtmult; int /*<<< orphan*/  wtpref; void* wtmax; int /*<<< orphan*/  rtmult; int /*<<< orphan*/  rtpref; void* rtmax; int /*<<< orphan*/  fattr; } ;
struct nfs_fh {int dummy; } ;
struct nfs2_fsstat {int /*<<< orphan*/  tsize; int /*<<< orphan*/  bsize; } ;

/* Variables and functions */
 size_t NFSPROC_STATFS ; 
 void* NFS_MAXDATA ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs_procedures ; 
 int rpc_call_sync (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_proc_fsinfo(struct nfs_server *server, struct nfs_fh *fhandle,
			struct nfs_fsinfo *info)
{
	struct nfs2_fsstat fsinfo;
	struct rpc_message msg = {
		.rpc_proc	= &nfs_procedures[NFSPROC_STATFS],
		.rpc_argp	= fhandle,
		.rpc_resp	= &fsinfo,
	};
	int	status;

	dprintk("NFS call  fsinfo\n");
	nfs_fattr_init(info->fattr);
	status = rpc_call_sync(server->client, &msg, 0);
	dprintk("NFS reply fsinfo: %d\n", status);
	if (status)
		goto out;
	info->rtmax  = NFS_MAXDATA;
	info->rtpref = fsinfo.tsize;
	info->rtmult = fsinfo.bsize;
	info->wtmax  = NFS_MAXDATA;
	info->wtpref = fsinfo.tsize;
	info->wtmult = fsinfo.bsize;
	info->dtpref = fsinfo.tsize;
	info->maxfilesize = 0x7FFFFFFF;
	info->lease_time = 0;
out:
	return status;
}