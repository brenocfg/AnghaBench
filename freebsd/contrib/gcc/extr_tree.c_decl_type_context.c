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
typedef  scalar_t__ tree ;

/* Variables and functions */
#define  BLOCK 135 
 scalar_t__ BLOCK_SUPERCONTEXT (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
#define  FUNCTION_DECL 134 
#define  NAMESPACE_DECL 133 
 scalar_t__ NULL_TREE ; 
#define  QUAL_UNION_TYPE 132 
#define  RECORD_TYPE 131 
#define  TRANSLATION_UNIT_DECL 130 
 int TREE_CODE (scalar_t__) ; 
#define  TYPE_DECL 129 
#define  UNION_TYPE 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

tree
decl_type_context (tree decl)
{
  tree context = DECL_CONTEXT (decl);

  while (context)
    switch (TREE_CODE (context))
      {
      case NAMESPACE_DECL:
      case TRANSLATION_UNIT_DECL:
	return NULL_TREE;

      case RECORD_TYPE:
      case UNION_TYPE:
      case QUAL_UNION_TYPE:
	return context;

      case TYPE_DECL:
      case FUNCTION_DECL:
	context = DECL_CONTEXT (context);
	break;

      case BLOCK:
	context = BLOCK_SUPERCONTEXT (context);
	break;

      default:
	gcc_unreachable ();
      }

  return NULL_TREE;
}