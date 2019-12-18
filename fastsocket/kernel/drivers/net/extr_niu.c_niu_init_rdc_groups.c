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
struct rdc_table {int /*<<< orphan*/ * rxdma_channel; } ;
struct niu_rdc_tables {int first_table_num; int num_tables; struct rdc_table* tables; } ;
struct niu {size_t port; TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * rdc_default; struct niu_rdc_tables* rdc_group_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_RDC (size_t) ; 
 int NIU_RDC_TABLE_SLOTS ; 
 int /*<<< orphan*/  RDC_TBL (int,int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_init_rdc_groups(struct niu *np)
{
	struct niu_rdc_tables *tp = &np->parent->rdc_group_cfg[np->port];
	int i, first_table_num = tp->first_table_num;

	for (i = 0; i < tp->num_tables; i++) {
		struct rdc_table *tbl = &tp->tables[i];
		int this_table = first_table_num + i;
		int slot;

		for (slot = 0; slot < NIU_RDC_TABLE_SLOTS; slot++)
			nw64(RDC_TBL(this_table, slot),
			     tbl->rxdma_channel[slot]);
	}

	nw64(DEF_RDC(np->port), np->parent->rdc_default[np->port]);
}