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
struct svc_fh {TYPE_1__* fh_dentry; } ;
struct nfs4_stateid {TYPE_2__* st_file; } ;
struct TYPE_4__ {scalar_t__ fi_inode; } ;
struct TYPE_3__ {scalar_t__ d_inode; } ;

/* Variables and functions */

__attribute__((used)) static inline int
nfs4_check_fh(struct svc_fh *fhp, struct nfs4_stateid *stp)
{
	return fhp->fh_dentry->d_inode != stp->st_file->fi_inode;
}