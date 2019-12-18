#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_size; } ;
struct nfs_inode {int /*<<< orphan*/  change_attr; TYPE_4__ vfs_inode; } ;
struct nfs_fscache_inode_auxdata {int /*<<< orphan*/  change_attr; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  auxdata ;
struct TYPE_7__ {TYPE_2__* nfs_client; } ;
struct TYPE_6__ {TYPE_1__* rpc_ops; } ;
struct TYPE_5__ {int version; } ;

/* Variables and functions */
 TYPE_3__* NFS_SERVER (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (void*,struct nfs_fscache_inode_auxdata*,int) ; 
 int /*<<< orphan*/  memset (struct nfs_fscache_inode_auxdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t nfs_fscache_inode_get_aux(const void *cookie_netfs_data,
					  void *buffer, uint16_t bufmax)
{
	struct nfs_fscache_inode_auxdata auxdata;
	const struct nfs_inode *nfsi = cookie_netfs_data;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.size = nfsi->vfs_inode.i_size;
	auxdata.mtime = nfsi->vfs_inode.i_mtime;
	auxdata.ctime = nfsi->vfs_inode.i_ctime;

	if (NFS_SERVER(&nfsi->vfs_inode)->nfs_client->rpc_ops->version == 4)
		auxdata.change_attr = nfsi->change_attr;

	if (bufmax > sizeof(auxdata))
		bufmax = sizeof(auxdata);

	memcpy(buffer, &auxdata, bufmax);
	return bufmax;
}