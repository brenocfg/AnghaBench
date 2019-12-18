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
struct bstp_state {int dummy; } ;
struct bstp_port {int bp_active; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bp_next ; 
 int /*<<< orphan*/  bstp_disable_port (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_reinit (struct bstp_state*) ; 

void
bstp_disable(struct bstp_port *bp)
{
	struct bstp_state *bs = bp->bp_bs;

	KASSERT(bp->bp_active == 1, ("not a bstp member"));

	BSTP_LOCK(bs);
	bstp_disable_port(bs, bp);
	LIST_REMOVE(bp, bp_next);
	bp->bp_active = 0;
	bstp_reinit(bs);
	BSTP_UNLOCK(bs);
}