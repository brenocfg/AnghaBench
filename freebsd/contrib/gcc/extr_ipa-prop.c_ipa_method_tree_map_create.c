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
struct TYPE_2__ {int /*<<< orphan*/  ipa_param_tree; } ;

/* Variables and functions */
 TYPE_1__* IPA_NODE_REF (struct cgraph_node*) ; 
 int /*<<< orphan*/  XCNEWVEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipa_method_formal_count (struct cgraph_node*) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static inline void
ipa_method_tree_map_create (struct cgraph_node *mt)
{
  IPA_NODE_REF (mt)->ipa_param_tree =
    XCNEWVEC (tree, ipa_method_formal_count (mt));
}