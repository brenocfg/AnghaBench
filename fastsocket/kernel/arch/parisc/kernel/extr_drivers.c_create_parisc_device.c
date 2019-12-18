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
struct device {int dummy; } ;
struct parisc_device {struct device dev; } ;
struct hardware_path {int* bc; int mod; } ;

/* Variables and functions */
 struct parisc_device* alloc_tree_node (struct device*,int) ; 
 struct device root ; 

__attribute__((used)) static struct parisc_device *create_parisc_device(struct hardware_path *modpath)
{
	int i;
	struct device *parent = &root;
	for (i = 0; i < 6; i++) {
		if (modpath->bc[i] == -1)
			continue;
		parent = &alloc_tree_node(parent, modpath->bc[i])->dev;
	}
	return alloc_tree_node(parent, modpath->mod);
}