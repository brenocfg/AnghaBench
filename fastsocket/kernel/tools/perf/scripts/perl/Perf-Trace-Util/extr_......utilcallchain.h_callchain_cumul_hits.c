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
typedef  scalar_t__ u64 ;
struct callchain_node {scalar_t__ children_hit; scalar_t__ hit; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 callchain_cumul_hits(struct callchain_node *node)
{
	return node->hit + node->children_hit;
}