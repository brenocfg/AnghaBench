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
struct ipa_dfs_info {int /*<<< orphan*/  aux; } ;
struct cgraph_node {struct ipa_dfs_info* aux; } ;
typedef  int /*<<< orphan*/  funct_state ;

/* Variables and functions */

__attribute__((used)) static inline funct_state
get_function_state (struct cgraph_node *node)
{
  struct ipa_dfs_info * info = node->aux;
  return info->aux;
}