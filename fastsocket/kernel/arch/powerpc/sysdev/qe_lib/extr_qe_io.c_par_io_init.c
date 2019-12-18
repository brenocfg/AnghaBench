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
typedef  int /*<<< orphan*/  u32 ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  num_par_io_ports ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  par_io ; 

int par_io_init(struct device_node *np)
{
	struct resource res;
	int ret;
	const u32 *num_ports;

	/* Map Parallel I/O ports registers */
	ret = of_address_to_resource(np, 0, &res);
	if (ret)
		return ret;
	par_io = ioremap(res.start, res.end - res.start + 1);

	num_ports = of_get_property(np, "num-ports", NULL);
	if (num_ports)
		num_par_io_ports = *num_ports;

	return 0;
}