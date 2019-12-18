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
struct cryptocop_dma_desc {struct cryptocop_dma_desc* next; TYPE_1__* dma_descr; } ;
typedef  int /*<<< orphan*/  dma_descr_data ;
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ virt_to_phys (TYPE_1__*) ; 

__attribute__((used)) static void setup_descr_chain(struct cryptocop_dma_desc *cd)
{
	DEBUG(printk("setup_descr_chain: entering\n"));
	while (cd) {
		if (cd->next) {
			cd->dma_descr->next = (dma_descr_data*)virt_to_phys(cd->next->dma_descr);
		} else {
			cd->dma_descr->next = NULL;
		}
		cd = cd->next;
	}
	DEBUG(printk("setup_descr_chain: exit\n"));
}