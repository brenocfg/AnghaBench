#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct int_tree_map {int /*<<< orphan*/ * to; } ;
struct TYPE_3__ {int /*<<< orphan*/  hti; } ;
typedef  TYPE_1__ referenced_var_iterator ;

/* Variables and functions */
 scalar_t__ first_htab_element (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  referenced_vars ; 

__attribute__((used)) static inline tree
first_referenced_var (referenced_var_iterator *iter)
{
  struct int_tree_map *itm;
  itm = (struct int_tree_map *) first_htab_element (&iter->hti,
                                                    referenced_vars);
  if (!itm) 
    return NULL;
  return itm->to;
}