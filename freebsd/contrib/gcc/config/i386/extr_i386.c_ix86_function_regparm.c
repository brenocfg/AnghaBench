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
typedef  scalar_t__ tree ;
struct cgraph_local_info {scalar_t__ local; } ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ force_align_arg_pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NO_STATIC_CHAIN (scalar_t__) ; 
 TYPE_2__* DECL_STRUCT_FUNCTION (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 struct cgraph_local_info* cgraph_local_info (scalar_t__) ; 
 scalar_t__ decl_function_context (scalar_t__) ; 
 scalar_t__ flag_unit_at_a_time ; 
 scalar_t__* global_regs ; 
 char* ix86_force_align_arg_pointer_string ; 
 int ix86_regparm ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_flag ; 

__attribute__((used)) static int
ix86_function_regparm (tree type, tree decl)
{
  tree attr;
  int regparm = ix86_regparm;
  bool user_convention = false;

  if (!TARGET_64BIT)
    {
      attr = lookup_attribute ("regparm", TYPE_ATTRIBUTES (type));
      if (attr)
	{
	  regparm = TREE_INT_CST_LOW (TREE_VALUE (TREE_VALUE (attr)));
	  user_convention = true;
	}

      if (lookup_attribute ("fastcall", TYPE_ATTRIBUTES (type)))
	{
	  regparm = 2;
	  user_convention = true;
	}

      /* Use register calling convention for local functions when possible.  */
      if (!TARGET_64BIT && !user_convention && decl
	  && flag_unit_at_a_time && !profile_flag)
	{
	  struct cgraph_local_info *i = cgraph_local_info (decl);
	  if (i && i->local)
	    {
	      int local_regparm, globals = 0, regno;

	      /* Make sure no regparm register is taken by a global register
		 variable.  */
	      for (local_regparm = 0; local_regparm < 3; local_regparm++)
		if (global_regs[local_regparm])
		  break;
	      /* We can't use regparm(3) for nested functions as these use
		 static chain pointer in third argument.  */
	      if (local_regparm == 3
		  && decl_function_context (decl)
		  && !DECL_NO_STATIC_CHAIN (decl))
		local_regparm = 2;
	      /* If the function realigns its stackpointer, the
		 prologue will clobber %ecx.  If we've already
		 generated code for the callee, the callee
		 DECL_STRUCT_FUNCTION is gone, so we fall back to
		 scanning the attributes for the self-realigning
		 property.  */
	      if ((DECL_STRUCT_FUNCTION (decl)
		   && DECL_STRUCT_FUNCTION (decl)->machine->force_align_arg_pointer)
		  || (!DECL_STRUCT_FUNCTION (decl)
		      && lookup_attribute (ix86_force_align_arg_pointer_string,
					   TYPE_ATTRIBUTES (TREE_TYPE (decl)))))
		local_regparm = 2;
	      /* Each global register variable increases register preassure,
		 so the more global reg vars there are, the smaller regparm
		 optimization use, unless requested by the user explicitly.  */
	      for (regno = 0; regno < 6; regno++)
		if (global_regs[regno])
		  globals++;
	      local_regparm
		= globals < local_regparm ? local_regparm - globals : 0;

	      if (local_regparm > regparm)
		regparm = local_regparm;
	    }
	}
    }
  return regparm;
}