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
typedef  int phys_addr_t ;

/* Variables and functions */
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 void* of_get_property (struct device_node*,char*,unsigned int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_translate_address (struct device_node*,void const*) ; 
 int tsi108_csr_base ; 

phys_addr_t get_csrbase(void)
{
	struct device_node *tsi;

	if (tsi108_csr_base != -1)
		return tsi108_csr_base;

	tsi = of_find_node_by_type(NULL, "tsi-bridge");
	if (tsi) {
		unsigned int size;
		const void *prop = of_get_property(tsi, "reg", &size);
		tsi108_csr_base = of_translate_address(tsi, prop);
		of_node_put(tsi);
	};
	return tsi108_csr_base;
}