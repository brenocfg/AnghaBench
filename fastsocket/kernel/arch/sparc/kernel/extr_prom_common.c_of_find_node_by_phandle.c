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
struct device_node {scalar_t__ node; struct device_node* allnext; } ;
typedef  scalar_t__ phandle ;

/* Variables and functions */
 struct device_node* allnodes ; 

struct device_node *of_find_node_by_phandle(phandle handle)
{
	struct device_node *np;

	for (np = allnodes; np; np = np->allnext)
		if (np->node == handle)
			break;

	return np;
}