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

/* Variables and functions */
 int /*<<< orphan*/  NODE_INTERNAL ; 
 scalar_t__* internal_node_num_keys (void*) ; 
 int /*<<< orphan*/  set_node_root (void*,int) ; 
 int /*<<< orphan*/  set_node_type (void*,int /*<<< orphan*/ ) ; 

void initialize_internal_node(void* node) {
  set_node_type(node, NODE_INTERNAL);
  set_node_root(node, false);
  *internal_node_num_keys(node) = 0;
}