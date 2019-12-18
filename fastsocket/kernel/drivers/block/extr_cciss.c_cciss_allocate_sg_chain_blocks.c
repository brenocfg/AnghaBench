#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pdev; } ;
typedef  TYPE_2__ ctlr_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  SGDescriptor_struct ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cciss_free_sg_chain_blocks (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SGDescriptor_struct **cciss_allocate_sg_chain_blocks(
	ctlr_info_t *h, int chainsize, int nr_cmds)
{
	int j;
	SGDescriptor_struct **cmd_sg_list;

	if (chainsize <= 0)
		return NULL;

	cmd_sg_list = kmalloc(sizeof(*cmd_sg_list) * nr_cmds, GFP_KERNEL);
	if (!cmd_sg_list)
		return NULL;

	/* Build up chain blocks for each command */
	for (j = 0; j < nr_cmds; j++) {
		/* Need a block of chainsized s/g elements. */
		cmd_sg_list[j] = kmalloc((chainsize *
			sizeof(*cmd_sg_list[j])), GFP_KERNEL);
		if (!cmd_sg_list[j]) {
			dev_err(&h->pdev->dev, "Cannot get memory "
				"for s/g chains.\n");
			goto clean;
		}
	}
	return cmd_sg_list;
clean:
	cciss_free_sg_chain_blocks(cmd_sg_list, nr_cmds);
	return NULL;
}