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
struct sockaddr {int dummy; } ;
struct nlmclnt_initdata {int nfs_version; int noresvport; int /*<<< orphan*/  protocol; int /*<<< orphan*/  addrlen; struct sockaddr* address; int /*<<< orphan*/  hostname; } ;
struct nlm_host {int dummy; } ;
struct nfs_server {int flags; int /*<<< orphan*/  destroy; struct nlm_host* nlm_host; struct nfs_client* nfs_client; } ;
struct nfs_client {int cl_proto; TYPE_1__* rpc_ops; int /*<<< orphan*/  cl_addrlen; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_hostname; } ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ IS_ERR (struct nlm_host*) ; 
 int NFS_MOUNT_LOCAL_FCNTL ; 
 int NFS_MOUNT_LOCAL_FLOCK ; 
 int NFS_MOUNT_NORESVPORT ; 
 int PTR_ERR (struct nlm_host*) ; 
#define  XPRT_TRANSPORT_UDP 128 
 int /*<<< orphan*/  nfs_destroy_server ; 
 struct nlm_host* nlmclnt_init (struct nlmclnt_initdata*) ; 

__attribute__((used)) static int nfs_start_lockd(struct nfs_server *server)
{
	struct nlm_host *host;
	struct nfs_client *clp = server->nfs_client;
	struct nlmclnt_initdata nlm_init = {
		.hostname	= clp->cl_hostname,
		.address	= (struct sockaddr *)&clp->cl_addr,
		.addrlen	= clp->cl_addrlen,
		.nfs_version	= clp->rpc_ops->version,
		.noresvport	= server->flags & NFS_MOUNT_NORESVPORT ?
					1 : 0,
	};

	if (nlm_init.nfs_version > 3)
		return 0;
	if ((server->flags & NFS_MOUNT_LOCAL_FLOCK) &&
			(server->flags & NFS_MOUNT_LOCAL_FCNTL))
		return 0;

	switch (clp->cl_proto) {
		default:
			nlm_init.protocol = IPPROTO_TCP;
			break;
		case XPRT_TRANSPORT_UDP:
			nlm_init.protocol = IPPROTO_UDP;
	}

	host = nlmclnt_init(&nlm_init);
	if (IS_ERR(host))
		return PTR_ERR(host);

	server->nlm_host = host;
	server->destroy = nfs_destroy_server;
	return 0;
}