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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
#define  MINUS_EXPR 132 
#define  NOP_EXPR 131 
#define  PLUS_EXPR 130 
 size_t TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TRUNC_DIV_EXPR 129 
#define  TRUNC_MOD_EXPR 128 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char const*) ; 
 char** tree_code_name ; 

__attribute__((used)) static void
pp_cxx_assignment_operator (cxx_pretty_printer *pp, tree t)
{
  const char *op;

  switch (TREE_CODE (t))
    {
    case NOP_EXPR:
      op = "=";
      break;

    case PLUS_EXPR:
      op = "+=";
      break;

    case MINUS_EXPR:
      op = "-=";
      break;

    case TRUNC_DIV_EXPR:
      op = "/=";
      break;

    case TRUNC_MOD_EXPR:
      op = "%=";
      break;

    default:
      op = tree_code_name[TREE_CODE (t)];
      break;
    }

  pp_cxx_identifier (pp, op);
}