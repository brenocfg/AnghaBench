#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_6__ {int /*<<< orphan*/  format_num; int /*<<< orphan*/  first_arg_num; int /*<<< orphan*/  format_type; } ;
typedef  TYPE_2__ function_format_info ;
struct TYPE_5__ {int /*<<< orphan*/  (* getdecls ) () ;} ;
struct TYPE_7__ {TYPE_1__ decls; } ;

/* Variables and functions */
 scalar_t__ IDENTIFIER_NODE ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wformat ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_format_type (char const*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  format_type_error ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_3__ lang_hooks ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
decode_format_attr (tree args, function_format_info *info, int validated_p)
{
  tree format_type_id = TREE_VALUE (args);
  tree format_num_expr = TREE_VALUE (TREE_CHAIN (args));
  tree first_arg_num_expr
    = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (args)));

  if (TREE_CODE (format_type_id) != IDENTIFIER_NODE)
    {
      gcc_assert (!validated_p);
      error ("%Junrecognized format specifier", lang_hooks.decls.getdecls ());
      return false;
    }
  else
    {
      const char *p = IDENTIFIER_POINTER (format_type_id);

      info->format_type = decode_format_type (p);

      if (info->format_type == format_type_error)
	{
	  gcc_assert (!validated_p);
	  warning (OPT_Wformat, "%qE is an unrecognized format function type",
		   format_type_id);
	  return false;
	}
    }

  if (!get_constant (format_num_expr, &info->format_num, validated_p))
    {
      error ("format string has invalid operand number");
      return false;
    }

  if (!get_constant (first_arg_num_expr, &info->first_arg_num, validated_p))
    {
      error ("%<...%> has invalid operand number");
      return false;
    }

  if (info->first_arg_num != 0 && info->first_arg_num <= info->format_num)
    {
      gcc_assert (!validated_p);
      error ("format string argument follows the args to be formatted");
      return false;
    }

  return true;
}