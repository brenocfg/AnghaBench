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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int MAX_NR_HVC_CONSOLES ; 
 int /*<<< orphan*/  hvc_get_put_ops ; 
 int /*<<< orphan*/  hvc_instantiate (int /*<<< orphan*/  const,int,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_find_node_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int hvc_find_vtys(void)
{
	struct device_node *vty;
	int num_found = 0;

	for (vty = of_find_node_by_name(NULL, "vty"); vty != NULL;
			vty = of_find_node_by_name(vty, "vty")) {
		const uint32_t *vtermno;

		/* We have statically defined space for only a certain number
		 * of console adapters.
		 */
		if (num_found >= MAX_NR_HVC_CONSOLES) {
			of_node_put(vty);
			break;
		}

		vtermno = of_get_property(vty, "reg", NULL);
		if (!vtermno)
			continue;

		if (of_device_is_compatible(vty, "hvterm1")) {
			hvc_instantiate(*vtermno, num_found, &hvc_get_put_ops);
			++num_found;
		}
	}

	return num_found;
}