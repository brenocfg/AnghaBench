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
typedef  int u32 ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBUS_TARG_WRPTR ; 
 int /*<<< orphan*/  IL49_SCD_QUEUE_RDPTR (int) ; 
 int /*<<< orphan*/  il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  il_wr_prph (struct il_priv*,int /*<<< orphan*/ ,int) ; 

void
il4965_set_wr_ptrs(struct il_priv *il, int txq_id, u32 idx)
{
	il_wr(il, HBUS_TARG_WRPTR, (idx & 0xff) | (txq_id << 8));
	il_wr_prph(il, IL49_SCD_QUEUE_RDPTR(txq_id), idx);
}