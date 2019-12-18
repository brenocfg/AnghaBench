#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgraph_node {int dummy; } ;
typedef  int /*<<< orphan*/  gcov_type ;
struct TYPE_2__ {int /*<<< orphan*/  count_scale; } ;

/* Variables and functions */
 TYPE_1__* IPA_NODE_REF (struct cgraph_node*) ; 

__attribute__((used)) static inline void
ipcp_method_set_scale (struct cgraph_node *node, gcov_type count)
{
  IPA_NODE_REF (node)->count_scale = count;
}