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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {scalar_t__ data; } ;
struct nfsd4_open {int* op_bmval; TYPE_4__* op_stateowner; int /*<<< orphan*/  op_cinfo; int /*<<< orphan*/ * op_acl; TYPE_2__ op_fname; int /*<<< orphan*/  op_createmode; int /*<<< orphan*/  op_truncate; TYPE_1__ op_verf; int /*<<< orphan*/  op_iattr; scalar_t__ op_create; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_7__ {int /*<<< orphan*/  rp_openfh; } ;
struct TYPE_8__ {TYPE_3__ so_replay; } ;

/* Variables and functions */
 int FATTR4_WORD1_TIME_ACCESS ; 
 int FATTR4_WORD1_TIME_MODIFY ; 
 int /*<<< orphan*/  NFS4_CREATE_EXCLUSIVE ; 
 int /*<<< orphan*/  NFS4_FHSIZE ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 scalar_t__ do_open_permission (struct svc_rqst*,struct svc_fh*,struct nfsd4_open*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_set_nfs4_acl (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fh_copy_shallow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fh_dup2 (struct svc_fh*,struct svc_fh*) ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_unlock (struct svc_fh*) ; 
 scalar_t__ is_create_with_attrs (struct nfsd4_open*) ; 
 scalar_t__ nfsd_check_obj_isreg (struct svc_fh*) ; 
 scalar_t__ nfsd_create_v3 (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ nfsd_lookup (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct svc_fh*) ; 
 int /*<<< orphan*/  set_change_info (int /*<<< orphan*/ *,struct svc_fh*) ; 

__attribute__((used)) static __be32
do_open_lookup(struct svc_rqst *rqstp, struct svc_fh *current_fh, struct nfsd4_open *open)
{
	struct svc_fh resfh;
	__be32 status;
	int created = 0;

	fh_init(&resfh, NFS4_FHSIZE);
	open->op_truncate = 0;

	if (open->op_create) {
		/* FIXME: check session persistence and pnfs flags.
		 * The nfsv4.1 spec requires the following semantics:
		 *
		 * Persistent   | pNFS   | Server REQUIRED | Client Allowed
		 * Reply Cache  | server |                 |
		 * -------------+--------+-----------------+--------------------
		 * no           | no     | EXCLUSIVE4_1    | EXCLUSIVE4_1
		 *              |        |                 | (SHOULD)
		 *              |        | and EXCLUSIVE4  | or EXCLUSIVE4
		 *              |        |                 | (SHOULD NOT)
		 * no           | yes    | EXCLUSIVE4_1    | EXCLUSIVE4_1
		 * yes          | no     | GUARDED4        | GUARDED4
		 * yes          | yes    | GUARDED4        | GUARDED4
		 */

		/*
		 * Note: create modes (UNCHECKED,GUARDED...) are the same
		 * in NFSv4 as in v3.
		 */
		status = nfsd_create_v3(rqstp, current_fh, open->op_fname.data,
					open->op_fname.len, &open->op_iattr,
					&resfh, open->op_createmode,
					(u32 *)open->op_verf.data,
					&open->op_truncate, &created);

		/*
		 * Following rfc 3530 14.2.16, use the returned bitmask
		 * to indicate which attributes we used to store the
		 * verifier:
		 */
		if (open->op_createmode == NFS4_CREATE_EXCLUSIVE && status == 0)
			open->op_bmval[1] = (FATTR4_WORD1_TIME_ACCESS |
						FATTR4_WORD1_TIME_MODIFY);
	} else {
		status = nfsd_lookup(rqstp, current_fh,
				     open->op_fname.data, open->op_fname.len, &resfh);
		fh_unlock(current_fh);
	}
	if (status)
		goto out;
	status = nfsd_check_obj_isreg(&resfh);
	if (status)
		goto out;

	if (is_create_with_attrs(open) && open->op_acl != NULL)
		do_set_nfs4_acl(rqstp, &resfh, open->op_acl, open->op_bmval);

	set_change_info(&open->op_cinfo, current_fh);
	fh_dup2(current_fh, &resfh);

	/* set reply cache */
	fh_copy_shallow(&open->op_stateowner->so_replay.rp_openfh,
			&resfh.fh_handle);
	if (!created)
		status = do_open_permission(rqstp, current_fh, open,
					    NFSD_MAY_NOP);

out:
	fh_put(&resfh);
	return status;
}