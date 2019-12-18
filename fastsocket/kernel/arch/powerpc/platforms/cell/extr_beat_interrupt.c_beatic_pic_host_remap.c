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
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  beat_construct_and_connect_irq_plug (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void beatic_pic_host_remap(struct irq_host *h, unsigned int virq,
			       irq_hw_number_t hw)
{
	beat_construct_and_connect_irq_plug(virq, hw);
}