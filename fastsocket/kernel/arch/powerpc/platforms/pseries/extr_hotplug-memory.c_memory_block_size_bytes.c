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
 struct device_node* of_find_node_by_path (char*) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

u32 memory_block_size_bytes(void)
{
	struct device_node *np;
	unsigned int memblock_size = 0;

	np = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	if (np) {
		const unsigned long *size;

		size = of_get_property(np, "ibm,lmb-size", NULL);
		memblock_size = size ? *size : 0;

		of_node_put(np);
	} else {
		unsigned int memzero_size = 0;
		const unsigned int *regs;

		np = of_find_node_by_path("/memory@0");
		if (np) {
			regs = of_get_property(np, "reg", NULL);
			memzero_size = regs ? regs[3] : 0;
			of_node_put(np);
		}

		if (memzero_size) {
			/* We now know the size of memory@0, use this to find
			 * the first memoryblock and get its size.
			 */
			char buf[64];

			sprintf(buf, "/memory@%x", memzero_size);
			np = of_find_node_by_path(buf);
			if (np) {
				regs = of_get_property(np, "reg", NULL);
				memblock_size = regs ? regs[3] : 0;
				of_node_put(np);
			}
		}
	}

	return memblock_size;
}