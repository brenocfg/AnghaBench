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
struct ht_irq_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_irq (unsigned int) ; 
 struct ht_irq_cfg* get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct ht_irq_cfg*) ; 
 int /*<<< orphan*/  set_irq_chip (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_data (unsigned int,int /*<<< orphan*/ *) ; 

void ht_destroy_irq(unsigned int irq)
{
	struct ht_irq_cfg *cfg;

	cfg = get_irq_data(irq);
	set_irq_chip(irq, NULL);
	set_irq_data(irq, NULL);
	destroy_irq(irq);

	kfree(cfg);
}