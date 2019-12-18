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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static int xics_host_match(struct irq_host *h, struct device_node *node)
{
	/* IBM machines have interrupt parents of various funky types for things
	 * like vdevices, events, etc... The trick we use here is to match
	 * everything here except the legacy 8259 which is compatible "chrp,iic"
	 */
	return !of_device_is_compatible(node, "chrp,iic");
}