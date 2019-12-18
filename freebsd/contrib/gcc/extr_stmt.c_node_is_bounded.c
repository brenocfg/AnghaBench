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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  case_node_ptr ;

/* Variables and functions */
 scalar_t__ node_has_high_bound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ node_has_low_bound (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
node_is_bounded (case_node_ptr node, tree index_type)
{
  return (node_has_low_bound (node, index_type)
	  && node_has_high_bound (node, index_type));
}