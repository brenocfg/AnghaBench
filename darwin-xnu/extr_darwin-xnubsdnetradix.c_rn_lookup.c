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
struct radix_node_head {int dummy; } ;
struct radix_node {int dummy; } ;

/* Variables and functions */
 struct radix_node* rn_lookup_args (void*,void*,struct radix_node_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct radix_node *
rn_lookup(void *v_arg, void *m_arg, struct radix_node_head *head)
{
	return (rn_lookup_args(v_arg, m_arg, head, NULL, NULL));
}