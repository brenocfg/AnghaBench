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

/* Variables and functions */
#define  ADDR_EXPR 128 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 char const* IDENTIFIER_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
get_name (tree t)
{
  tree stripped_decl;

  stripped_decl = t;
  STRIP_NOPS (stripped_decl);
  if (DECL_P (stripped_decl) && DECL_NAME (stripped_decl))
    return IDENTIFIER_POINTER (DECL_NAME (stripped_decl));
  else
    {
      switch (TREE_CODE (stripped_decl))
	{
	case ADDR_EXPR:
	  return get_name (TREE_OPERAND (stripped_decl, 0));
	  break;
	default:
	  return NULL;
	}
    }
}