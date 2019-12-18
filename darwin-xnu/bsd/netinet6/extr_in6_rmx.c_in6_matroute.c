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
 struct radix_node* in6_matroute_args (void*,struct radix_node_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct radix_node *
in6_matroute(void *v_arg, struct radix_node_head *head)
{
	return (in6_matroute_args(v_arg, head, NULL, NULL));
}