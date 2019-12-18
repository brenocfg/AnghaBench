#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* splay_tree_node ;
struct TYPE_5__ {char const* (* decl_printable_name ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {scalar_t__ value; } ;

/* Variables and functions */
 TYPE_3__ lang_hooks ; 
 int /*<<< orphan*/  reference_vars_to_consider ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int) ; 
 char const* stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *
get_static_name (int index)
{
  splay_tree_node stn = 
    splay_tree_lookup (reference_vars_to_consider, index);
  if (stn)
    return lang_hooks.decl_printable_name ((tree)(stn->value), 2);
  return NULL;
}