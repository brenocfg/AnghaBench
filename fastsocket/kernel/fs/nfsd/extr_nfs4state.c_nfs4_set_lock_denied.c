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
struct TYPE_4__ {scalar_t__ cl_id; scalar_t__ cl_boot; } ;
struct nfsd4_lock_denied {scalar_t__ ld_start; scalar_t__ ld_length; int /*<<< orphan*/  ld_type; TYPE_2__ ld_clientid; struct nfs4_stateowner* ld_sop; } ;
struct nfs4_stateowner {TYPE_1__* so_client; int /*<<< orphan*/  so_ref; } ;
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; scalar_t__ fl_type; scalar_t__ fl_owner; int /*<<< orphan*/ * fl_lmops; } ;
struct TYPE_3__ {TYPE_2__ cl_clientid; } ;

/* Variables and functions */
 scalar_t__ F_RDLCK ; 
 scalar_t__ NFS4_MAX_UINT64 ; 
 int /*<<< orphan*/  NFS4_READ_LT ; 
 int /*<<< orphan*/  NFS4_WRITE_LT ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_posix_mng_ops ; 

__attribute__((used)) static inline void
nfs4_set_lock_denied(struct file_lock *fl, struct nfsd4_lock_denied *deny)
{
	struct nfs4_stateowner *sop;

	if (fl->fl_lmops == &nfsd_posix_mng_ops) {
		sop = (struct nfs4_stateowner *) fl->fl_owner;
		kref_get(&sop->so_ref);
		deny->ld_sop = sop;
		deny->ld_clientid = sop->so_client->cl_clientid;
	} else {
		deny->ld_sop = NULL;
		deny->ld_clientid.cl_boot = 0;
		deny->ld_clientid.cl_id = 0;
	}
	deny->ld_start = fl->fl_start;
	deny->ld_length = NFS4_MAX_UINT64;
	if (fl->fl_end != NFS4_MAX_UINT64)
		deny->ld_length = fl->fl_end - fl->fl_start + 1;        
	deny->ld_type = NFS4_READ_LT;
	if (fl->fl_type != F_RDLCK)
		deny->ld_type = NFS4_WRITE_LT;
}