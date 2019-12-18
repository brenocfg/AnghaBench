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
struct ipr_data {size_t ipr_idx; int shift; } ;
struct TYPE_2__ {unsigned long* ipr_offsets; } ;

/* Variables and functions */
 int __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  __raw_writew (int,unsigned long) ; 
 TYPE_1__* get_ipr_desc (unsigned int) ; 
 struct ipr_data* get_irq_chip_data (unsigned int) ; 

__attribute__((used)) static void disable_ipr_irq(unsigned int irq)
{
	struct ipr_data *p = get_irq_chip_data(irq);
	unsigned long addr = get_ipr_desc(irq)->ipr_offsets[p->ipr_idx];
	/* Set the priority in IPR to 0 */
	__raw_writew(__raw_readw(addr) & (0xffff ^ (0xf << p->shift)), addr);
	(void)__raw_readw(addr);	/* Read back to flush write posting */
}