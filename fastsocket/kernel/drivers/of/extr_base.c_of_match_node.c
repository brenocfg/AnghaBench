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
struct of_device_id {scalar_t__* compatible; scalar_t__* type; scalar_t__* name; } ;
struct device_node {scalar_t__ type; scalar_t__ name; } ;

/* Variables and functions */
 int of_device_is_compatible (struct device_node const*,scalar_t__*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__*,scalar_t__) ; 

const struct of_device_id *of_match_node(const struct of_device_id *matches,
					 const struct device_node *node)
{
	while (matches->name[0] || matches->type[0] || matches->compatible[0]) {
		int match = 1;
		if (matches->name[0])
			match &= node->name
				&& !strcmp(matches->name, node->name);
		if (matches->type[0])
			match &= node->type
				&& !strcmp(matches->type, node->type);
		if (matches->compatible[0])
			match &= of_device_is_compatible(node,
						matches->compatible);
		if (match)
			return matches;
		matches++;
	}
	return NULL;
}