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
typedef  scalar_t__ u32 ;
struct svc_fh {int /*<<< orphan*/  fh_handle; } ;
struct nfs4_stateid {struct nfs4_file* st_file; } ;
struct nfs4_file {int /*<<< orphan*/  fi_delegations; scalar_t__ fi_had_conflict; } ;
struct TYPE_4__ {int /*<<< orphan*/  cb_work; } ;
struct TYPE_3__ {scalar_t__ si_generation; scalar_t__ si_fileid; scalar_t__ si_stateownerid; int /*<<< orphan*/  si_boot; } ;
struct nfs4_delegation {TYPE_2__ dl_recall; int /*<<< orphan*/  dl_perclnt; int /*<<< orphan*/  dl_perfile; int /*<<< orphan*/  dl_count; scalar_t__ dl_time; int /*<<< orphan*/  dl_fh; TYPE_1__ dl_stateid; scalar_t__ dl_type; int /*<<< orphan*/ * dl_flock; struct nfs4_file* dl_file; struct nfs4_client* dl_client; int /*<<< orphan*/  dl_recall_lru; } ;
struct nfs4_client {int /*<<< orphan*/  cl_delegations; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NFS4_OPEN_DELEGATE_READ ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  boot_time ; 
 int /*<<< orphan*/  current_delegid ; 
 int /*<<< orphan*/  deleg_slab ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  fh_copy_shallow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_nfs4_file (struct nfs4_file*) ; 
 struct nfs4_delegation* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ max_delegations ; 
 int /*<<< orphan*/  nfs4_file_get_access (struct nfs4_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_do_callback_rpc ; 
 scalar_t__ num_delegations ; 

__attribute__((used)) static struct nfs4_delegation *
alloc_init_deleg(struct nfs4_client *clp, struct nfs4_stateid *stp, struct svc_fh *current_fh, u32 type)
{
	struct nfs4_delegation *dp;
	struct nfs4_file *fp = stp->st_file;

	dprintk("NFSD alloc_init_deleg\n");
	/*
	 * Major work on the lease subsystem (for example, to support
	 * calbacks on stat) will be required before we can support
	 * write delegations properly.
	 */
	if (type != NFS4_OPEN_DELEGATE_READ)
		return NULL;
	if (fp->fi_had_conflict)
		return NULL;
	if (num_delegations > max_delegations)
		return NULL;
	dp = kmem_cache_alloc(deleg_slab, GFP_KERNEL);
	if (dp == NULL)
		return dp;
	num_delegations++;
	INIT_LIST_HEAD(&dp->dl_perfile);
	INIT_LIST_HEAD(&dp->dl_perclnt);
	INIT_LIST_HEAD(&dp->dl_recall_lru);
	dp->dl_client = clp;
	get_nfs4_file(fp);
	dp->dl_file = fp;
	nfs4_file_get_access(fp, O_RDONLY);
	dp->dl_flock = NULL;
	dp->dl_type = type;
	dp->dl_stateid.si_boot = boot_time;
	dp->dl_stateid.si_stateownerid = current_delegid++;
	dp->dl_stateid.si_fileid = 0;
	dp->dl_stateid.si_generation = 0;
	fh_copy_shallow(&dp->dl_fh, &current_fh->fh_handle);
	dp->dl_time = 0;
	atomic_set(&dp->dl_count, 1);
	list_add(&dp->dl_perfile, &fp->fi_delegations);
	list_add(&dp->dl_perclnt, &clp->cl_delegations);
	INIT_WORK(&dp->dl_recall.cb_work, nfsd4_do_callback_rpc);
	return dp;
}