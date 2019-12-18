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
struct nfs4_state {TYPE_2__* owner; int /*<<< orphan*/  stateid; int /*<<< orphan*/  seqlock; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ so_sequence; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int nfs4_copy_open_stateid(nfs4_stateid *dst, struct nfs4_state *state)
{
	int ret;
	int seq;

	do {
		seq = read_seqbegin(&state->seqlock);
		nfs4_stateid_copy(dst, &state->stateid);
		ret = 0;
		smp_rmb();
		if (!list_empty(&state->owner->so_sequence.list))
			ret = -EWOULDBLOCK;
	} while (read_seqretry(&state->seqlock, seq));
	return ret;
}