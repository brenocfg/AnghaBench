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
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char const*,int*) ; 

struct device_node *
of_parse_phandle(struct device_node *np, const char *phandle_name, int index)
{
	const phandle *phandle;
	int size;

	phandle = of_get_property(np, phandle_name, &size);
	if ((!phandle) || (size < sizeof(*phandle) * (index + 1)))
		return NULL;

	return of_find_node_by_phandle(phandle[index]);
}