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
typedef  int u32 ;
struct nfsd4_open {int op_rflags; int* op_bmval; int op_delegate_type; int op_recall; int /*<<< orphan*/  op_stateowner; int /*<<< orphan*/  op_delegate_stateid; int /*<<< orphan*/  op_cinfo; int /*<<< orphan*/  op_stateid; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ENCODE_SEQID_OP_HEAD ; 
 int /*<<< orphan*/  ENCODE_SEQID_OP_TAIL (int /*<<< orphan*/ ) ; 
 int NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 int NFS4_LIMIT_SIZE ; 
#define  NFS4_OPEN_DELEGATE_NONE 130 
#define  NFS4_OPEN_DELEGATE_READ 129 
#define  NFS4_OPEN_DELEGATE_WRITE 128 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int /*<<< orphan*/  WRITE32 (int) ; 
 int /*<<< orphan*/  nfsd4_encode_stateid (struct nfsd4_compoundres*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_cinfo (scalar_t__**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_encode_open(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_open *open)
{
	__be32 *p;
	ENCODE_SEQID_OP_HEAD;

	if (nfserr)
		goto out;

	nfsd4_encode_stateid(resp, &open->op_stateid);
	RESERVE_SPACE(40);
	write_cinfo(&p, &open->op_cinfo);
	WRITE32(open->op_rflags);
	WRITE32(2);
	WRITE32(open->op_bmval[0]);
	WRITE32(open->op_bmval[1]);
	WRITE32(open->op_delegate_type);
	ADJUST_ARGS();

	switch (open->op_delegate_type) {
	case NFS4_OPEN_DELEGATE_NONE:
		break;
	case NFS4_OPEN_DELEGATE_READ:
		nfsd4_encode_stateid(resp, &open->op_delegate_stateid);
		RESERVE_SPACE(20);
		WRITE32(open->op_recall);

		/*
		 * TODO: ACE's in delegations
		 */
		WRITE32(NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE);
		WRITE32(0);
		WRITE32(0);
		WRITE32(0);   /* XXX: is NULL principal ok? */
		ADJUST_ARGS();
		break;
	case NFS4_OPEN_DELEGATE_WRITE:
		nfsd4_encode_stateid(resp, &open->op_delegate_stateid);
		RESERVE_SPACE(32);
		WRITE32(0);

		/*
		 * TODO: space_limit's in delegations
		 */
		WRITE32(NFS4_LIMIT_SIZE);
		WRITE32(~(u32)0);
		WRITE32(~(u32)0);

		/*
		 * TODO: ACE's in delegations
		 */
		WRITE32(NFS4_ACE_ACCESS_ALLOWED_ACE_TYPE);
		WRITE32(0);
		WRITE32(0);
		WRITE32(0);   /* XXX: is NULL principal ok? */
		ADJUST_ARGS();
		break;
	default:
		BUG();
	}
	/* XXX save filehandle here */
out:
	ENCODE_SEQID_OP_TAIL(open->op_stateowner);
	return nfserr;
}