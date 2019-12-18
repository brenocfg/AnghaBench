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
typedef  int u8 ;
struct il_tx_queue {int swq_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline void
il_set_swq_id(struct il_tx_queue *txq, u8 ac, u8 hwq)
{
	BUG_ON(ac > 3);		/* only have 2 bits */
	BUG_ON(hwq > 31);	/* only use 5 bits */

	txq->swq_id = (hwq << 2) | ac;
}