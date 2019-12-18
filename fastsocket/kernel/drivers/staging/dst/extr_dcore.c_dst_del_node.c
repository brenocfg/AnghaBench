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
struct dst_node {int dummy; } ;
struct dst_ctl {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int dst_node_remove_unload (struct dst_node*) ; 

__attribute__((used)) static int dst_del_node(struct dst_node *n, struct dst_ctl *ctl,
		void *data, unsigned int size)
{
	if (!n)
		return -ENODEV;

	return dst_node_remove_unload(n);
}