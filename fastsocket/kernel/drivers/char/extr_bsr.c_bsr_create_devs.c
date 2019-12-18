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
struct device_node {int dummy; } ;

/* Variables and functions */
 int bsr_add_node (struct device_node*) ; 
 struct device_node* of_find_compatible_node (struct device_node*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int bsr_create_devs(struct device_node *bn)
{
	int ret;

	while (bn) {
		ret = bsr_add_node(bn);
		if (ret) {
			of_node_put(bn);
			return ret;
		}
		bn = of_find_compatible_node(bn, NULL, "ibm,bsr");
	}
	return 0;
}