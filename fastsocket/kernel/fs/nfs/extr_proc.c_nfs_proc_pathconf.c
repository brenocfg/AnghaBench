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
struct nfs_pathconf {int /*<<< orphan*/  max_namelen; scalar_t__ max_link; } ;
struct nfs_fh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS2_MAXNAMLEN ; 

__attribute__((used)) static int
nfs_proc_pathconf(struct nfs_server *server, struct nfs_fh *fhandle,
		  struct nfs_pathconf *info)
{
	info->max_link = 0;
	info->max_namelen = NFS2_MAXNAMLEN;
	return 0;
}