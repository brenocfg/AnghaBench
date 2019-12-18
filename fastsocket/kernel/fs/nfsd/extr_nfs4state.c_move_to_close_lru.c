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
struct nfs4_stateowner {int /*<<< orphan*/  so_time; int /*<<< orphan*/  so_close_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_lru ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
move_to_close_lru(struct nfs4_stateowner *sop)
{
	dprintk("NFSD: move_to_close_lru nfs4_stateowner %p\n", sop);

	list_move_tail(&sop->so_close_lru, &close_lru);
	sop->so_time = get_seconds();
}