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
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  nodes_fold (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_onto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  nodes_weight (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void mpol_relative_nodemask(nodemask_t *ret, const nodemask_t *orig,
				   const nodemask_t *rel)
{
	nodemask_t tmp;
	nodes_fold(tmp, *orig, nodes_weight(*rel));
	nodes_onto(*ret, tmp, *rel);
}