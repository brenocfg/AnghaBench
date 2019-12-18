#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fh_dentry; TYPE_2__* fh_export; } ;
struct nfsd_diropres {int /*<<< orphan*/  stat; TYPE_3__ fh; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_5__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 scalar_t__ nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd_return_dirop(__be32 err, struct nfsd_diropres *resp)
{
	if (err) return err;
	return nfserrno(vfs_getattr(resp->fh.fh_export->ex_path.mnt,
				    resp->fh.fh_dentry,
				    &resp->stat));
}