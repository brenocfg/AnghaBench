#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  protocol; void* port; } ;
struct TYPE_3__ {void* port; } ;
struct nfs_parsed_mount_data {int auth_flavor_len; unsigned int version; int /*<<< orphan*/  lsm_opts; scalar_t__ minorversion; int /*<<< orphan*/ * auth_flavors; TYPE_2__ nfs_server; TYPE_1__ mount_server; int /*<<< orphan*/  acdirmax; int /*<<< orphan*/  acdirmin; int /*<<< orphan*/  acregmax; int /*<<< orphan*/  acregmin; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFS_DEF_ACDIRMAX ; 
 int /*<<< orphan*/  NFS_DEF_ACDIRMIN ; 
 int /*<<< orphan*/  NFS_DEF_ACREGMAX ; 
 int /*<<< orphan*/  NFS_DEF_ACREGMIN ; 
 void* NFS_UNSPEC_PORT ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int /*<<< orphan*/  XPRT_TRANSPORT_TCP ; 
 struct nfs_parsed_mount_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_init_mnt_opts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_parsed_mount_data *nfs_alloc_parsed_mount_data(unsigned int version)
{
	struct nfs_parsed_mount_data *data;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (data) {
		data->acregmin		= NFS_DEF_ACREGMIN;
		data->acregmax		= NFS_DEF_ACREGMAX;
		data->acdirmin		= NFS_DEF_ACDIRMIN;
		data->acdirmax		= NFS_DEF_ACDIRMAX;
		data->mount_server.port	= NFS_UNSPEC_PORT;
		data->nfs_server.port	= NFS_UNSPEC_PORT;
		data->nfs_server.protocol = XPRT_TRANSPORT_TCP;
		data->auth_flavors[0]	= RPC_AUTH_UNIX;
		data->auth_flavor_len	= 1;
		data->version		= version;
		data->minorversion	= 0;
		security_init_mnt_opts(&data->lsm_opts);
	}
	return data;
}