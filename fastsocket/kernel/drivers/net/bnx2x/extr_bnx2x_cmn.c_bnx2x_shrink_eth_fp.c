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
struct bnx2x_fp_txdata {int dummy; } ;
struct bnx2x_fastpath {int /*<<< orphan*/ ** txdata_ptr; } ;
struct bnx2x {int max_cos; int /*<<< orphan*/ * bnx2x_txq; struct bnx2x_fastpath* fp; } ;

/* Variables and functions */
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bnx2x_shrink_eth_fp(struct bnx2x *bp, int delta)
{
	int i, cos, old_eth_num = BNX2X_NUM_ETH_QUEUES(bp);

	/* Queue pointer cannot be re-set on an fp-basis, as moving pointer
	 * backward along the array could cause memory to be overridden
	 */
	for (cos = 1; cos < bp->max_cos; cos++) {
		for (i = 0; i < old_eth_num - delta; i++) {
			struct bnx2x_fastpath *fp = &bp->fp[i];
			int new_idx = cos * (old_eth_num - delta) + i;

			memcpy(&bp->bnx2x_txq[new_idx], fp->txdata_ptr[cos],
			       sizeof(struct bnx2x_fp_txdata));
			fp->txdata_ptr[cos] = &bp->bnx2x_txq[new_idx];
		}
	}
}