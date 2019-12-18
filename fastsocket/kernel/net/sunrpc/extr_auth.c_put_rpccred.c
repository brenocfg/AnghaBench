#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {TYPE_1__* cr_ops; int /*<<< orphan*/  cr_lru; int /*<<< orphan*/  cr_expire; int /*<<< orphan*/  cr_flags; int /*<<< orphan*/  cr_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* crdestroy ) (struct rpc_cred*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPCAUTH_CRED_HASHED ; 
 int /*<<< orphan*/  RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cred_unused ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  number_cred_unused ; 
 int /*<<< orphan*/  rpc_credcache_lock ; 
 int /*<<< orphan*/  rpcauth_unhash_cred (struct rpc_cred*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_cred*) ; 
 int /*<<< orphan*/  stub2 (struct rpc_cred*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
put_rpccred(struct rpc_cred *cred)
{
	/* Fast path for unhashed credentials */
	if (test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags) == 0) {
		if (atomic_dec_and_test(&cred->cr_count))
			cred->cr_ops->crdestroy(cred);
		return;
	}

	if (!atomic_dec_and_lock(&cred->cr_count, &rpc_credcache_lock))
		return;
	if (!list_empty(&cred->cr_lru)) {
		number_cred_unused--;
		list_del_init(&cred->cr_lru);
	}
	if (test_bit(RPCAUTH_CRED_HASHED, &cred->cr_flags) != 0) {
		if (test_bit(RPCAUTH_CRED_UPTODATE, &cred->cr_flags) != 0) {
			cred->cr_expire = jiffies;
			list_add_tail(&cred->cr_lru, &cred_unused);
			number_cred_unused++;
			goto out_nodestroy;
		}
		if (!rpcauth_unhash_cred(cred)) {
			/* We were hashed and someone looked us up... */
			goto out_nodestroy;
		}
	}
	spin_unlock(&rpc_credcache_lock);
	cred->cr_ops->crdestroy(cred);
	return;
out_nodestroy:
	spin_unlock(&rpc_credcache_lock);
}