#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
struct gimplify_omp_ctx {int /*<<< orphan*/  privatized_types; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* omp_firstprivatize_type_sizes ) (struct gimplify_omp_ctx*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
#define  ARRAY_TYPE 137 
#define  BOOLEAN_TYPE 136 
 int /*<<< orphan*/  DECL_FIELD_OFFSET (int /*<<< orphan*/ *) ; 
#define  ENUMERAL_TYPE 135 
 int FIELD_DECL ; 
#define  INTEGER_TYPE 134 
#define  POINTER_TYPE 133 
#define  QUAL_UNION_TYPE 132 
#define  REAL_TYPE 131 
#define  RECORD_TYPE 130 
#define  REFERENCE_TYPE 129 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_DOMAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_FIELDS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_MAIN_VARIANT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (int /*<<< orphan*/ *) ; 
#define  UNION_TYPE 128 
 int /*<<< orphan*/ * error_mark_node ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  omp_firstprivatize_variable (struct gimplify_omp_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ pointer_set_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gimplify_omp_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
omp_firstprivatize_type_sizes (struct gimplify_omp_ctx *ctx, tree type)
{
  if (type == NULL || type == error_mark_node)
    return;
  type = TYPE_MAIN_VARIANT (type);

  if (pointer_set_insert (ctx->privatized_types, type))
    return;

  switch (TREE_CODE (type))
    {
    case INTEGER_TYPE:
    case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:
    case REAL_TYPE:
      omp_firstprivatize_variable (ctx, TYPE_MIN_VALUE (type));
      omp_firstprivatize_variable (ctx, TYPE_MAX_VALUE (type));
      break;

    case ARRAY_TYPE:
      omp_firstprivatize_type_sizes (ctx, TREE_TYPE (type));
      omp_firstprivatize_type_sizes (ctx, TYPE_DOMAIN (type));
      break;

    case RECORD_TYPE:
    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      {
	tree field;
	for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
	  if (TREE_CODE (field) == FIELD_DECL)
	    {
	      omp_firstprivatize_variable (ctx, DECL_FIELD_OFFSET (field));
	      omp_firstprivatize_type_sizes (ctx, TREE_TYPE (field));
	    }
      }
      break;

    case POINTER_TYPE:
    case REFERENCE_TYPE:
      omp_firstprivatize_type_sizes (ctx, TREE_TYPE (type));
      break;

    default:
      break;
    }

  omp_firstprivatize_variable (ctx, TYPE_SIZE (type));
  omp_firstprivatize_variable (ctx, TYPE_SIZE_UNIT (type));
  lang_hooks.types.omp_firstprivatize_type_sizes (ctx, type);
}