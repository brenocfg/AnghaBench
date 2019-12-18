#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_4__ {scalar_t__ value; scalar_t__ mem_ref; } ;
typedef  TYPE_1__ prop_value_t ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (scalar_t__) ; 
 size_t SSA_NAME_VERSION (scalar_t__) ; 
 TYPE_1__* copy_of ; 
 int /*<<< orphan*/  stmt_may_generate_copy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline prop_value_t *
get_copy_of_val (tree var)
{
  prop_value_t *val = &copy_of[SSA_NAME_VERSION (var)];

  if (val->value == NULL_TREE
      && !stmt_may_generate_copy (SSA_NAME_DEF_STMT (var)))
    {
      /* If the variable will never generate a useful copy relation,
	 make it its own copy.  */
      val->value = var;
      val->mem_ref = NULL_TREE;
    }

  return val;
}