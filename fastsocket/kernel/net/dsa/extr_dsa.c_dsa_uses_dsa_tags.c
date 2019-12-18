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
struct dsa_switch_tree {scalar_t__ tag_protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_DSA ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

bool dsa_uses_dsa_tags(void *dsa_ptr)
{
	struct dsa_switch_tree *dst = dsa_ptr;

	return !!(dst->tag_protocol == htons(ETH_P_DSA));
}