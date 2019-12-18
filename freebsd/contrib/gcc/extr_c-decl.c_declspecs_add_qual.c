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
struct c_declspecs {int non_sc_seen_p; int declspecs_seen_p; int const_p; int volatile_p; int restrict_p; } ;
typedef  enum rid { ____Placeholder_rid } rid ;

/* Variables and functions */
 scalar_t__ C_IS_RESERVED_WORD (int /*<<< orphan*/ ) ; 
 int C_RID_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IDENTIFIER_NODE ; 
#define  RID_CONST 130 
#define  RID_RESTRICT 129 
#define  RID_VOLATILE 128 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ) ; 

struct c_declspecs *
declspecs_add_qual (struct c_declspecs *specs, tree qual)
{
  enum rid i;
  bool dupe = false;
  specs->non_sc_seen_p = true;
  specs->declspecs_seen_p = true;
  gcc_assert (TREE_CODE (qual) == IDENTIFIER_NODE
	      && C_IS_RESERVED_WORD (qual));
  i = C_RID_CODE (qual);
  switch (i)
    {
    case RID_CONST:
      dupe = specs->const_p;
      specs->const_p = true;
      break;
    case RID_VOLATILE:
      dupe = specs->volatile_p;
      specs->volatile_p = true;
      break;
    case RID_RESTRICT:
      dupe = specs->restrict_p;
      specs->restrict_p = true;
      break;
    default:
      gcc_unreachable ();
    }
  if (dupe && pedantic && !flag_isoc99)
    pedwarn ("duplicate %qE", qual);
  return specs;
}