#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct z_candidate {scalar_t__ fn; } ;
struct TYPE_6__ {int ellipsis_p; scalar_t__ bad_p; } ;
typedef  TYPE_1__ conversion ;

/* Variables and functions */
 scalar_t__ FUNCTION_TYPE ; 
 int LOOKUP_NORMAL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 struct z_candidate* add_candidate (struct z_candidate**,scalar_t__,scalar_t__,int,TYPE_1__**,scalar_t__,scalar_t__,int) ; 
 TYPE_1__** alloc_conversions (int) ; 
 TYPE_1__* build_identity_conv (scalar_t__,scalar_t__) ; 
 TYPE_1__* implicit_conversion (scalar_t__,scalar_t__,scalar_t__,int,int) ; 
 int list_length (scalar_t__) ; 
 scalar_t__ lvalue_type (scalar_t__) ; 
 int /*<<< orphan*/  sufficient_parms_p (scalar_t__) ; 
 scalar_t__ void_list_node ; 

__attribute__((used)) static struct z_candidate *
add_conv_candidate (struct z_candidate **candidates, tree fn, tree obj,
		    tree arglist, tree access_path, tree conversion_path)
{
  tree totype = TREE_TYPE (TREE_TYPE (fn));
  int i, len, viable, flags;
  tree parmlist, parmnode, argnode;
  conversion **convs;

  for (parmlist = totype; TREE_CODE (parmlist) != FUNCTION_TYPE; )
    parmlist = TREE_TYPE (parmlist);
  parmlist = TYPE_ARG_TYPES (parmlist);

  len = list_length (arglist) + 1;
  convs = alloc_conversions (len);
  parmnode = parmlist;
  argnode = arglist;
  viable = 1;
  flags = LOOKUP_NORMAL;

  /* Don't bother looking up the same type twice.  */
  if (*candidates && (*candidates)->fn == totype)
    return NULL;

  for (i = 0; i < len; ++i)
    {
      tree arg = i == 0 ? obj : TREE_VALUE (argnode);
      tree argtype = lvalue_type (arg);
      conversion *t;

      if (i == 0)
	t = implicit_conversion (totype, argtype, arg, /*c_cast_p=*/false,
				 flags);
      else if (parmnode == void_list_node)
	break;
      else if (parmnode)
	t = implicit_conversion (TREE_VALUE (parmnode), argtype, arg,
				 /*c_cast_p=*/false, flags);
      else
	{
	  t = build_identity_conv (argtype, arg);
	  t->ellipsis_p = true;
	}

      convs[i] = t;
      if (! t)
	break;

      if (t->bad_p)
	viable = -1;

      if (i == 0)
	continue;

      if (parmnode)
	parmnode = TREE_CHAIN (parmnode);
      argnode = TREE_CHAIN (argnode);
    }

  if (i < len)
    viable = 0;

  if (!sufficient_parms_p (parmnode))
    viable = 0;

  return add_candidate (candidates, totype, arglist, len, convs,
			access_path, conversion_path, viable);
}