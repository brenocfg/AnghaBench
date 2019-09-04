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
struct bstp_state {int /*<<< orphan*/  bs_bplist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK_DESTROY (struct bstp_state*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bstp_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_list ; 
 int /*<<< orphan*/  bsd_untimeout (int /*<<< orphan*/ ,struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_list_mtx ; 
 int /*<<< orphan*/  bstp_tick ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

void
bstp_detach(struct bstp_state *bs)
{
	KASSERT(LIST_EMPTY(&bs->bs_bplist), ("bstp still active"));

	lck_mtx_lock(bstp_list_mtx);
	LIST_REMOVE(bs, bs_list);
	lck_mtx_unlock(bstp_list_mtx);
	bsd_untimeout(bstp_tick, bs);
	BSTP_LOCK_DESTROY(bs);
}