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
typedef  scalar_t__ tree ;
struct cgraph_node {int dummy; } ;
struct TYPE_2__ {scalar_t__* ipa_param_tree; } ;

/* Variables and functions */
 TYPE_1__* IPA_NODE_REF (struct cgraph_node*) ; 
 int ipa_method_formal_count (struct cgraph_node*) ; 

__attribute__((used)) static int
ipa_method_tree_map (struct cgraph_node *mt, tree ptree)
{
  int i, count;

  count = ipa_method_formal_count (mt);
  for (i = 0; i < count; i++)
    if (IPA_NODE_REF (mt)->ipa_param_tree[i] == ptree)
      return i;

  return -1;
}