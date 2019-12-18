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
struct nfs4_stateid {int /*<<< orphan*/  st_access_bmap; struct nfs4_stateid* st_openstp; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int RD_STATE ; 
 int WR_STATE ; 
 int /*<<< orphan*/  access_permit_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_permit_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_openmode ; 

__attribute__((used)) static
__be32 nfs4_check_openmode(struct nfs4_stateid *stp, int flags)
{
        __be32 status = nfserr_openmode;

	/* For lock stateid's, we test the parent open, not the lock: */
	if (stp->st_openstp)
		stp = stp->st_openstp;
	if ((flags & WR_STATE) && (!access_permit_write(stp->st_access_bmap)))
                goto out;
	if ((flags & RD_STATE) && (!access_permit_read(stp->st_access_bmap)))
                goto out;
	status = nfs_ok;
out:
	return status;
}