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
struct nfs4_delegation {int /*<<< orphan*/  dl_file; scalar_t__ dl_flock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_delegation*) ; 
 struct file* find_readable_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_file_put_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_setlease (struct file*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
nfs4_close_delegation(struct nfs4_delegation *dp)
{
	struct file *filp = find_readable_file(dp->dl_file);

	dprintk("NFSD: close_delegation dp %p\n",dp);
	if (dp->dl_flock)
		vfs_setlease(filp, F_UNLCK, &dp->dl_flock);
	nfs4_file_put_access(dp->dl_file, O_RDONLY);
}