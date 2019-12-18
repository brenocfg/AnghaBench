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
 int nr_threads_per_core ; 
 struct device_node* of_find_node_by_type (int /*<<< orphan*/ *,char*) ; 
 int* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static void get_threads_per_core(void)
{
	struct device_node *dn = NULL;
	int len;
	const int *intserv;

	nr_threads_per_core = 1; /* default */

	dn = of_find_node_by_type(NULL, "cpu");
	intserv = of_get_property(dn, "ibm,ppc-interrupt-server#s", &len);
	if (intserv)
		nr_threads_per_core = len / sizeof(int);

	of_node_put(dn);
}