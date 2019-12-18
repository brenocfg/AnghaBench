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
struct TYPE_2__ {int need_abi_warning; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__ const) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__ const) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  abi_version_at_least (int) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 scalar_t__ size_binop (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_one_node ; 
 int /*<<< orphan*/  tree_low_cst (scalar_t__,int) ; 
 int /*<<< orphan*/  value_dependent_expression_p (scalar_t__) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_expression (scalar_t__) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unsigned_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_array_type (const tree type)
{
  write_char ('A');
  if (TYPE_DOMAIN (type))
    {
      tree index_type;
      tree max;

      index_type = TYPE_DOMAIN (type);
      /* The INDEX_TYPE gives the upper and lower bounds of the
	 array.  */
      max = TYPE_MAX_VALUE (index_type);
      if (TREE_CODE (max) == INTEGER_CST)
	{
	  /* The ABI specifies that we should mangle the number of
	     elements in the array, not the largest allowed index.  */
	  max = size_binop (PLUS_EXPR, max, size_one_node);
	  write_unsigned_number (tree_low_cst (max, 1));
	}
      else
	{
	  max = TREE_OPERAND (max, 0);
	  if (!abi_version_at_least (2))
	    {
	      /* value_dependent_expression_p presumes nothing is
		 dependent when PROCESSING_TEMPLATE_DECL is zero.  */
	      ++processing_template_decl;
	      if (!value_dependent_expression_p (max))
		G.need_abi_warning = 1;
	      --processing_template_decl;
	    }
	  write_expression (max);
	}

    }
  write_char ('_');
  write_type (TREE_TYPE (type));
}