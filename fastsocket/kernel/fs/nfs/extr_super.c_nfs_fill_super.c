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
struct super_block {int s_time_gran; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_flags; scalar_t__ s_blocksize_bits; scalar_t__ s_blocksize; } ;
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs_parsed_mount_data {scalar_t__ bsize; } ;
struct TYPE_4__ {TYPE_1__* rpc_ops; } ;
struct TYPE_3__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_POSIXACL ; 
 struct nfs_server* NFS_SB (struct super_block*) ; 
 scalar_t__ nfs_block_size (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  nfs_initialise_sb (struct super_block*) ; 
 int /*<<< orphan*/  nfs_sops ; 

__attribute__((used)) static void nfs_fill_super(struct super_block *sb,
			   struct nfs_parsed_mount_data *data)
{
	struct nfs_server *server = NFS_SB(sb);

	sb->s_blocksize_bits = 0;
	sb->s_blocksize = 0;
	if (data->bsize)
		sb->s_blocksize = nfs_block_size(data->bsize, &sb->s_blocksize_bits);

	if (server->nfs_client->rpc_ops->version == 3) {
		/* The VFS shouldn't apply the umask to mode bits. We will do
		 * so ourselves when necessary.
		 */
		sb->s_flags |= MS_POSIXACL;
		sb->s_time_gran = 1;
	}

	sb->s_op = &nfs_sops;
 	nfs_initialise_sb(sb);
}