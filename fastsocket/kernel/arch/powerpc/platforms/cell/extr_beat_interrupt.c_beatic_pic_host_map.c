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
struct irq_host {int dummy; } ;
struct irq_desc {int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQ_LEVEL ; 
 scalar_t__ beat_construct_and_connect_irq_plug (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beatic_pic ; 
 struct irq_desc* get_irq_desc (unsigned int) ; 
 int /*<<< orphan*/  handle_fasteoi_irq ; 
 int /*<<< orphan*/  set_irq_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int beatic_pic_host_map(struct irq_host *h, unsigned int virq,
			       irq_hw_number_t hw)
{
	struct irq_desc *desc = get_irq_desc(virq);
	int64_t	err;

	err = beat_construct_and_connect_irq_plug(virq, hw);
	if (err < 0)
		return -EIO;

	desc->status |= IRQ_LEVEL;
	set_irq_chip_and_handler(virq, &beatic_pic, handle_fasteoi_irq);
	return 0;
}