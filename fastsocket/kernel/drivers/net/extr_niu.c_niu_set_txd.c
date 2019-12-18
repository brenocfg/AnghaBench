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
typedef  int u64 ;
struct tx_ring_info {int /*<<< orphan*/ * descr; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int TX_DESC_NUM_PTR_SHIFT ; 
 int TX_DESC_SAD ; 
 int TX_DESC_TR_LEN_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static void niu_set_txd(struct tx_ring_info *rp, int index,
			u64 mapping, u64 len, u64 mark,
			u64 n_frags)
{
	__le64 *desc = &rp->descr[index];

	*desc = cpu_to_le64(mark |
			    (n_frags << TX_DESC_NUM_PTR_SHIFT) |
			    (len << TX_DESC_TR_LEN_SHIFT) |
			    (mapping & TX_DESC_SAD));
}