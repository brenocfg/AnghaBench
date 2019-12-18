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
struct function_list {int /*<<< orphan*/ * n_ctrs; int /*<<< orphan*/  checksum; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 unsigned int GCOV_COUNTERS ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_FIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_constructor_from_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cstu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_gcov_unsigned_t () ; 
 int /*<<< orphan*/  nreverse (int /*<<< orphan*/ ) ; 
 int prg_ctr_mask ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
build_fn_info_value (const struct function_list *function, tree type)
{
  tree value = NULL_TREE;
  tree fields = TYPE_FIELDS (type);
  unsigned ix;
  tree array_value = NULL_TREE;

  /* ident */
  value = tree_cons (fields, build_int_cstu (get_gcov_unsigned_t (),
					     function->ident), value);
  fields = TREE_CHAIN (fields);

  /* checksum */
  value = tree_cons (fields, build_int_cstu (get_gcov_unsigned_t (),
					     function->checksum), value);
  fields = TREE_CHAIN (fields);

  /* counters */
  for (ix = 0; ix != GCOV_COUNTERS; ix++)
    if (prg_ctr_mask & (1 << ix))
      {
	tree counters = build_int_cstu (get_gcov_unsigned_t (),
					function->n_ctrs[ix]);

	array_value = tree_cons (NULL_TREE, counters, array_value);
      }

  /* FIXME: use build_constructor directly.  */
  array_value = build_constructor_from_list (TREE_TYPE (fields),
					     nreverse (array_value));
  value = tree_cons (fields, array_value, value);

  /* FIXME: use build_constructor directly.  */
  value = build_constructor_from_list (type, nreverse (value));

  return value;
}