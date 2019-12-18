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
struct nfsd4_lock {int /*<<< orphan*/  lk_replay_owner; int /*<<< orphan*/  lk_denied; int /*<<< orphan*/  lk_resp_stateid; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENCODE_SEQID_OP_HEAD ; 
 int /*<<< orphan*/  ENCODE_SEQID_OP_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_encode_lock_denied (struct nfsd4_compoundres*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_encode_stateid (struct nfsd4_compoundres*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_denied ; 

__attribute__((used)) static __be32
nfsd4_encode_lock(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_lock *lock)
{
	ENCODE_SEQID_OP_HEAD;

	if (!nfserr)
		nfsd4_encode_stateid(resp, &lock->lk_resp_stateid);
	else if (nfserr == nfserr_denied)
		nfsd4_encode_lock_denied(resp, &lock->lk_denied);

	ENCODE_SEQID_OP_TAIL(lock->lk_replay_owner);
	return nfserr;
}