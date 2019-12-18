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
struct z_candidate {int dummy; } ;
struct TYPE_6__ {scalar_t__ bad_p; } ;
typedef  TYPE_1__ conversion ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  add_candidate (struct z_candidate**,scalar_t__,int /*<<< orphan*/ ,size_t,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__** alloc_conversions (size_t) ; 
 scalar_t__ boolean_type_node ; 
 TYPE_1__* build_identity_conv (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* implicit_conversion (scalar_t__,scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static void
build_builtin_candidate (struct z_candidate **candidates, tree fnname,
			 tree type1, tree type2, tree *args, tree *argtypes,
			 int flags)
{
  conversion *t;
  conversion **convs;
  size_t num_convs;
  int viable = 1, i;
  tree types[2];

  types[0] = type1;
  types[1] = type2;

  num_convs =  args[2] ? 3 : (args[1] ? 2 : 1);
  convs = alloc_conversions (num_convs);

  for (i = 0; i < 2; ++i)
    {
      if (! args[i])
	break;

      t = implicit_conversion (types[i], argtypes[i], args[i],
			       /*c_cast_p=*/false, flags);
      if (! t)
	{
	  viable = 0;
	  /* We need something for printing the candidate.  */
	  t = build_identity_conv (types[i], NULL_TREE);
	}
      else if (t->bad_p)
	viable = 0;
      convs[i] = t;
    }

  /* For COND_EXPR we rearranged the arguments; undo that now.  */
  if (args[2])
    {
      convs[2] = convs[1];
      convs[1] = convs[0];
      t = implicit_conversion (boolean_type_node, argtypes[2], args[2],
			       /*c_cast_p=*/false, flags);
      if (t)
	convs[0] = t;
      else
	viable = 0;
    }

  add_candidate (candidates, fnname, /*args=*/NULL_TREE,
		 num_convs, convs,
		 /*access_path=*/NULL_TREE,
		 /*conversion_path=*/NULL_TREE,
		 viable);
}