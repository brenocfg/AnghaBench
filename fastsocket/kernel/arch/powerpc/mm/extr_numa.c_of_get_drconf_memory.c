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
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int n_mem_addr_cells ; 
 int* of_get_property (struct device_node*,char*,int*) ; 

__attribute__((used)) static int of_get_drconf_memory(struct device_node *memory, const u32 **dm)
{
	const u32 *prop;
	u32 len, entries;

	prop = of_get_property(memory, "ibm,dynamic-memory", &len);
	if (!prop || len < sizeof(unsigned int))
		return 0;

	entries = *prop++;

	/* Now that we know the number of entries, revalidate the size
	 * of the property read in to ensure we have everything
	 */
	if (len < (entries * (n_mem_addr_cells + 4) + 1) * sizeof(unsigned int))
		return 0;

	*dm = prop;
	return entries;
}