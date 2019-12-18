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
struct assoc_arrays {int n_arrays; int array_sz; int const* arrays; } ;

/* Variables and functions */
 int* of_get_property (struct device_node*,char*,int*) ; 

__attribute__((used)) static int of_get_assoc_arrays(struct device_node *memory,
			       struct assoc_arrays *aa)
{
	const u32 *prop;
	u32 len;

	prop = of_get_property(memory, "ibm,associativity-lookup-arrays", &len);
	if (!prop || len < 2 * sizeof(unsigned int))
		return -1;

	aa->n_arrays = *prop++;
	aa->array_sz = *prop++;

	/* Now that we know the number of arrrays and size of each array,
	 * revalidate the size of the property read in.
	 */
	if (len < (aa->n_arrays * aa->array_sz + 2) * sizeof(unsigned int))
		return -1;

	aa->arrays = prop;
	return 0;
}