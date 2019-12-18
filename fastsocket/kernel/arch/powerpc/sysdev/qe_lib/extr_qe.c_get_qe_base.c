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
struct device_node {int dummy; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_translate_address (struct device_node*,int /*<<< orphan*/  const*) ; 
 int qebase ; 

phys_addr_t get_qe_base(void)
{
	struct device_node *qe;
	int size;
	const u32 *prop;

	if (qebase != -1)
		return qebase;

	qe = of_find_compatible_node(NULL, NULL, "fsl,qe");
	if (!qe) {
		qe = of_find_node_by_type(NULL, "qe");
		if (!qe)
			return qebase;
	}

	prop = of_get_property(qe, "reg", &size);
	if (prop && size >= sizeof(*prop))
		qebase = of_translate_address(qe, prop);
	of_node_put(qe);

	return qebase;
}