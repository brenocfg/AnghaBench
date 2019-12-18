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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_vec; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct nfsd4_write {unsigned long wr_buflen; unsigned long wr_bytes_written; int /*<<< orphan*/  wr_how_written; int /*<<< orphan*/  wr_vlen; int /*<<< orphan*/  wr_offset; TYPE_1__ wr_verifier; int /*<<< orphan*/  wr_stable_how; int /*<<< orphan*/  wr_stateid; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_MAX ; 
 int /*<<< orphan*/  WR_STATE ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  get_file (struct file*) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 scalar_t__ nfs4_preprocess_stateid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct file**) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd_write (struct svc_rqst*,int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserr_symlink ; 
 TYPE_2__ nfssvc_boot ; 

__attribute__((used)) static __be32
nfsd4_write(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    struct nfsd4_write *write)
{
	stateid_t *stateid = &write->wr_stateid;
	struct file *filp = NULL;
	u32 *p;
	__be32 status = nfs_ok;
	unsigned long cnt;

	/* no need to check permission - this will be done in nfsd_write() */

	if (write->wr_offset >= OFFSET_MAX)
		return nfserr_inval;

	nfs4_lock_state();
	status = nfs4_preprocess_stateid_op(cstate, stateid, WR_STATE, &filp);
	if (filp)
		get_file(filp);
	nfs4_unlock_state();

	if (status) {
		dprintk("NFSD: nfsd4_write: couldn't process stateid!\n");
		return status;
	}

	cnt = write->wr_buflen;
	write->wr_how_written = write->wr_stable_how;
	p = (u32 *)write->wr_verifier.data;
	*p++ = nfssvc_boot.tv_sec;
	*p++ = nfssvc_boot.tv_usec;

	status =  nfsd_write(rqstp, &cstate->current_fh, filp,
			     write->wr_offset, rqstp->rq_vec, write->wr_vlen,
			     &cnt, &write->wr_how_written);
	if (filp)
		fput(filp);

	write->wr_bytes_written = cnt;

	if (status == nfserr_symlink)
		status = nfserr_inval;
	return status;
}