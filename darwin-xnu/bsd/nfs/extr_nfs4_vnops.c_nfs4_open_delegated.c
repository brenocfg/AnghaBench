#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
struct vnop_access_args {int a_action; int /*<<< orphan*/  a_context; int /*<<< orphan*/  a_vp; int /*<<< orphan*/ * a_desc; } ;
struct nfs_open_file {int dummy; } ;
struct kauth_acl_eval {int ae_requested; int ae_count; scalar_t__ ae_result; int /*<<< orphan*/  ae_exp_gexec; int /*<<< orphan*/  ae_exp_gwrite; int /*<<< orphan*/  ae_exp_gread; int /*<<< orphan*/  ae_exp_gall; int /*<<< orphan*/  ae_options; TYPE_1__* ae_acl; } ;
typedef  TYPE_3__* nfsnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_7__ {scalar_t__ nva_uid; int /*<<< orphan*/  nva_gid; } ;
struct TYPE_6__ {scalar_t__ ace_flags; } ;
struct TYPE_8__ {TYPE_2__ n_vattr; TYPE_1__ n_dace; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  KAUTH_AEVAL_IN_GROUP ; 
 int /*<<< orphan*/  KAUTH_AEVAL_IS_OWNER ; 
 scalar_t__ KAUTH_RESULT_ALLOW ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_ALL_BITS ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_EXECUTE_BITS ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_READ_BITS ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_WRITE_BITS ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int /*<<< orphan*/  NFSTOV (TYPE_3__*) ; 
 int NFS_OPEN_SHARE_ACCESS_READ ; 
 int NFS_OPEN_SHARE_ACCESS_WRITE ; 
 int kauth_acl_evaluate (int /*<<< orphan*/ ,struct kauth_acl_eval*) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int kauth_cred_ismember_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nfs_open_file_add_open (struct nfs_open_file*,int,int,int) ; 
 int nfs_vnop_access (struct vnop_access_args*) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnop_access_desc ; 

int
nfs4_open_delegated(
	nfsnode_t np,
	struct nfs_open_file *nofp,
	uint32_t accessMode,
	uint32_t denyMode,
	vfs_context_t ctx)
{
	int error = 0, ismember, readtoo = 0, authorized = 0;
	uint32_t action;
	struct kauth_acl_eval eval;
	kauth_cred_t cred = vfs_context_ucred(ctx);

	if (!(accessMode & NFS_OPEN_SHARE_ACCESS_READ)) {
		/*
		 * Try to open it for read access too,
		 * so the buffer cache can read data.
		 */
		readtoo = 1;
		accessMode |= NFS_OPEN_SHARE_ACCESS_READ;
	}

tryagain:
	action = 0;
	if (accessMode & NFS_OPEN_SHARE_ACCESS_READ)
		action |= KAUTH_VNODE_READ_DATA;
	if (accessMode & NFS_OPEN_SHARE_ACCESS_WRITE)
		action |= KAUTH_VNODE_WRITE_DATA;

	/* evaluate ACE (if we have one) */
	if (np->n_dace.ace_flags) {
		eval.ae_requested = action;
		eval.ae_acl = &np->n_dace;
		eval.ae_count = 1;
		eval.ae_options = 0;
		if (np->n_vattr.nva_uid == kauth_cred_getuid(cred))
			eval.ae_options |= KAUTH_AEVAL_IS_OWNER;
		error = kauth_cred_ismember_gid(cred, np->n_vattr.nva_gid, &ismember);
		if (!error && ismember)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP;

		eval.ae_exp_gall = KAUTH_VNODE_GENERIC_ALL_BITS;
		eval.ae_exp_gread = KAUTH_VNODE_GENERIC_READ_BITS;
		eval.ae_exp_gwrite = KAUTH_VNODE_GENERIC_WRITE_BITS;
		eval.ae_exp_gexec = KAUTH_VNODE_GENERIC_EXECUTE_BITS;

		error = kauth_acl_evaluate(cred, &eval);

		if (!error && (eval.ae_result == KAUTH_RESULT_ALLOW))
			authorized = 1;
	}

	if (!authorized) {
		/* need to ask the server via ACCESS */
		struct vnop_access_args naa;
		naa.a_desc = &vnop_access_desc;
		naa.a_vp = NFSTOV(np);
		naa.a_action = action;
		naa.a_context = ctx;
		if (!(error = nfs_vnop_access(&naa)))
			authorized = 1;
	}

	if (!authorized) {
		if (readtoo) {
			/* try again without the extra read access */
			accessMode &= ~NFS_OPEN_SHARE_ACCESS_READ;
			readtoo = 0;
			goto tryagain;
		}
		return (error ? error : EACCES);
	}

	nfs_open_file_add_open(nofp, accessMode, denyMode, 1);

	return (0);
}