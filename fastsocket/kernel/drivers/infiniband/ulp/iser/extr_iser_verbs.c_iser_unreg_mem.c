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
struct iser_mem_reg {int /*<<< orphan*/ * mem_h; } ;
struct ib_pool_fmr {int dummy; } ;

/* Variables and functions */
 int ib_fmr_pool_unmap (struct ib_pool_fmr*) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 

void iser_unreg_mem(struct iser_mem_reg *reg)
{
	int ret;

	iser_dbg("PHYSICAL Mem.Unregister mem_h %p\n",reg->mem_h);

	ret = ib_fmr_pool_unmap((struct ib_pool_fmr *)reg->mem_h);
	if (ret)
		iser_err("ib_fmr_pool_unmap failed %d\n", ret);

	reg->mem_h = NULL;
}