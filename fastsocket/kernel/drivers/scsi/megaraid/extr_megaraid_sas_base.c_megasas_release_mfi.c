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
struct megasas_instance {int max_mfi_cmds; int /*<<< orphan*/  bar; int /*<<< orphan*/  pdev; int /*<<< orphan*/  reg_set; int /*<<< orphan*/  reply_queue_h; scalar_t__ reply_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_free_cmds (struct megasas_instance*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_selected_regions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void megasas_release_mfi(struct megasas_instance *instance)
{
	u32 reply_q_sz = sizeof(u32) *(instance->max_mfi_cmds + 1);

	if (instance->reply_queue)
		pci_free_consistent(instance->pdev, reply_q_sz,
			    instance->reply_queue, instance->reply_queue_h);

	megasas_free_cmds(instance);

	iounmap(instance->reg_set);

	pci_release_selected_regions(instance->pdev, instance->bar);
}