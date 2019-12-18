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
typedef  int /*<<< orphan*/  u64 ;
struct nfsd4_lock_denied {int ld_type; TYPE_2__* ld_sop; int /*<<< orphan*/  ld_clientid; int /*<<< orphan*/  ld_length; int /*<<< orphan*/  ld_start; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/  so_ref; TYPE_1__ so_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  RESERVE_SPACE (scalar_t__) ; 
 int /*<<< orphan*/  WRITE32 (int) ; 
 int /*<<< orphan*/  WRITE64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEMEM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ XDR_LEN (int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_free_stateowner ; 

__attribute__((used)) static void
nfsd4_encode_lock_denied(struct nfsd4_compoundres *resp, struct nfsd4_lock_denied *ld)
{
	__be32 *p;

	RESERVE_SPACE(32 + XDR_LEN(ld->ld_sop ? ld->ld_sop->so_owner.len : 0));
	WRITE64(ld->ld_start);
	WRITE64(ld->ld_length);
	WRITE32(ld->ld_type);
	if (ld->ld_sop) {
		WRITEMEM(&ld->ld_clientid, 8);
		WRITE32(ld->ld_sop->so_owner.len);
		WRITEMEM(ld->ld_sop->so_owner.data, ld->ld_sop->so_owner.len);
		kref_put(&ld->ld_sop->so_ref, nfs4_free_stateowner);
	}  else {  /* non - nfsv4 lock in conflict, no clientid nor owner */
		WRITE64((u64)0); /* clientid */
		WRITE32(0); /* length of owner name */
	}
	ADJUST_ARGS();
}