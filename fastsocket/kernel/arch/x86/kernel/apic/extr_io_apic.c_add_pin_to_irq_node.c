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
struct irq_cfg {int dummy; } ;

/* Variables and functions */
 scalar_t__ add_pin_to_irq_node_nopanic (struct irq_cfg*,int,int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void add_pin_to_irq_node(struct irq_cfg *cfg, int node, int apic, int pin)
{
	if (add_pin_to_irq_node_nopanic(cfg, node, apic, pin))
		panic("IO-APIC: failed to add irq-pin. Can not proceed\n");
}