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
struct nes_cm_node {int dummy; } ;

/* Variables and functions */
 int add_ref_cm_node (struct nes_cm_node*) ; 

int nes_add_ref_cm_node(struct nes_cm_node *cm_node)
{
	return add_ref_cm_node(cm_node);
}