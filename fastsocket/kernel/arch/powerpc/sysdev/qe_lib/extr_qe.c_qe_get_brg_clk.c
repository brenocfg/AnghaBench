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
typedef  unsigned int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 unsigned int brg_clk ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 unsigned int* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

unsigned int qe_get_brg_clk(void)
{
	struct device_node *qe;
	int size;
	const u32 *prop;

	if (brg_clk)
		return brg_clk;

	qe = of_find_compatible_node(NULL, NULL, "fsl,qe");
	if (!qe) {
		qe = of_find_node_by_type(NULL, "qe");
		if (!qe)
			return brg_clk;
	}

	prop = of_get_property(qe, "brg-frequency", &size);
	if (prop && size == sizeof(*prop))
		brg_clk = *prop;

	of_node_put(qe);

	return brg_clk;
}