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
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct TYPE_6__ {int ia_valid; scalar_t__ ia_size; } ;
struct nfsd4_open {int op_truncate; TYPE_3__ op_iattr; TYPE_2__* op_stateowner; int /*<<< orphan*/  op_cinfo; int /*<<< orphan*/  op_clientid; } ;
struct nfsd4_change_info {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  rp_openfh; } ;
struct TYPE_5__ {TYPE_1__ so_replay; } ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int /*<<< orphan*/  NFSD_MAY_OWNER_OVERRIDE ; 
 int /*<<< orphan*/  do_open_permission (struct svc_rqst*,struct svc_fh*,struct nfsd4_open*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy_shallow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs4_check_open_reclaim (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
do_open_fhandle(struct svc_rqst *rqstp, struct svc_fh *current_fh, struct nfsd4_open *open)
{
	__be32 status;

	/* Only reclaims from previously confirmed clients are valid */
	if ((status = nfs4_check_open_reclaim(&open->op_clientid)))
		return status;

	/* We don't know the target directory, and therefore can not
	* set the change info
	*/

	memset(&open->op_cinfo, 0, sizeof(struct nfsd4_change_info));

	/* set replay cache */
	fh_copy_shallow(&open->op_stateowner->so_replay.rp_openfh,
			&current_fh->fh_handle);

	open->op_truncate = (open->op_iattr.ia_valid & ATTR_SIZE) &&
		(open->op_iattr.ia_size == 0);

	status = do_open_permission(rqstp, current_fh, open,
				    NFSD_MAY_OWNER_OVERRIDE);

	return status;
}