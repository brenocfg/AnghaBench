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
struct nfs_server {int dummy; } ;

/* Variables and functions */
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 
 int /*<<< orphan*/  nfs_free_server (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs_fscache_release_super_cookie (struct super_block*) ; 

__attribute__((used)) static void nfs_kill_super(struct super_block *s)
{
	struct nfs_server *server = NFS_SB(s);

	kill_anon_super(s);
	nfs_fscache_release_super_cookie(s);
	nfs_free_server(server);
}