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
typedef  char* tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
#define  ARRAY_REF 133 
#define  COND_EXPR 132 
#define  IMAGPART_EXPR 131 
 int MODIFY_EXPR ; 
#define  POSTDECREMENT_EXPR 130 
#define  POSTINCREMENT_EXPR 129 
#define  REALPART_EXPR 128 
 TYPE_2__* assignment_operator_name_info ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,char const*,...) ; 
 TYPE_1__* operator_name_info ; 

__attribute__((used)) static void
op_error (enum tree_code code, enum tree_code code2,
	  tree arg1, tree arg2, tree arg3, const char *problem)
{
  const char *opname;

  if (code == MODIFY_EXPR)
    opname = assignment_operator_name_info[code2].name;
  else
    opname = operator_name_info[code].name;

  switch (code)
    {
    case COND_EXPR:
      error ("%s for ternary %<operator?:%> in %<%E ? %E : %E%>",
	     problem, arg1, arg2, arg3);
      break;

    case POSTINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
      error ("%s for %<operator%s%> in %<%E%s%>", problem, opname, arg1, opname);
      break;

    case ARRAY_REF:
      error ("%s for %<operator[]%> in %<%E[%E]%>", problem, arg1, arg2);
      break;

    case REALPART_EXPR:
    case IMAGPART_EXPR:
      error ("%s for %qs in %<%s %E%>", problem, opname, opname, arg1);
      break;

    default:
      if (arg2)
	error ("%s for %<operator%s%> in %<%E %s %E%>",
	       problem, opname, arg1, opname, arg2);
      else
	error ("%s for %<operator%s%> in %<%s%E%>",
	       problem, opname, opname, arg1);
      break;
    }
}