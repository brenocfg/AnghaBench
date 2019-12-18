#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_5__ {int /*<<< orphan*/ * receiver_decl; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 int /*<<< orphan*/  COMPONENT_REF ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_fold_indirect_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_field (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * maybe_lookup_field (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static tree
build_receiver_ref (tree var, bool by_ref, omp_context *ctx)
{
  tree x, field = lookup_field (var, ctx);

  /* If the receiver record type was remapped in the child function,
     remap the field into the new record type.  */
  x = maybe_lookup_field (field, ctx);
  if (x != NULL)
    field = x;

  x = build_fold_indirect_ref (ctx->receiver_decl);
  x = build3 (COMPONENT_REF, TREE_TYPE (field), x, field, NULL);
  if (by_ref)
    x = build_fold_indirect_ref (x);

  return x;
}