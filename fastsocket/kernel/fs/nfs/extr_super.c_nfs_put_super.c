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
struct super_block {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  backing_dev_info; } ;

/* Variables and functions */
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  bdi_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_put_super(struct super_block *s)
{
	struct nfs_server *server = NFS_SB(s);

	bdi_unregister(&server->backing_dev_info);
}