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
struct parisc_device {int dummy; } ;
struct match_id_data {char id; struct parisc_device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct parisc_device* create_tree_node (char,struct device*) ; 
 scalar_t__ device_for_each_child (struct device*,struct match_id_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_by_id ; 

__attribute__((used)) static struct parisc_device * alloc_tree_node(struct device *parent, char id)
{
	struct match_id_data d = {
		.id = id,
	};
	if (device_for_each_child(parent, &d, match_by_id))
		return d.dev;
	else
		return create_tree_node(id, parent);
}