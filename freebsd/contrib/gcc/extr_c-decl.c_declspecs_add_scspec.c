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
struct c_declspecs {int declspecs_seen_p; int inline_p; int thread_p; int storage_class; scalar_t__ non_sc_seen_p; } ;
typedef  enum rid { ____Placeholder_rid } rid ;
typedef  enum c_storage_class { ____Placeholder_c_storage_class } c_storage_class ;

/* Variables and functions */
 scalar_t__ C_IS_RESERVED_WORD (int /*<<< orphan*/ ) ; 
 int C_RID_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 int /*<<< orphan*/  OPT_Wextra ; 
#define  RID_AUTO 134 
#define  RID_EXTERN 133 
#define  RID_INLINE 132 
#define  RID_REGISTER 131 
#define  RID_STATIC 130 
#define  RID_THREAD 129 
#define  RID_TYPEDEF 128 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int csc_auto ; 
 int csc_extern ; 
 int csc_none ; 
 int csc_register ; 
 int csc_static ; 
 int csc_typedef ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ extra_warnings ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct c_declspecs *
declspecs_add_scspec (struct c_declspecs *specs, tree scspec)
{
  enum rid i;
  enum c_storage_class n = csc_none;
  bool dupe = false;
  specs->declspecs_seen_p = true;
  gcc_assert (TREE_CODE (scspec) == IDENTIFIER_NODE
	      && C_IS_RESERVED_WORD (scspec));
  i = C_RID_CODE (scspec);
  if (extra_warnings && specs->non_sc_seen_p)
    warning (OPT_Wextra, "%qE is not at beginning of declaration", scspec);
  switch (i)
    {
    case RID_INLINE:
      /* C99 permits duplicate inline.  Although of doubtful utility,
	 it seems simplest to permit it in gnu89 mode as well, as
	 there is also little utility in maintaining this as a
	 difference between gnu89 and C99 inline.  */
      dupe = false;
      specs->inline_p = true;
      break;
    case RID_THREAD:
      dupe = specs->thread_p;
      if (specs->storage_class == csc_auto)
	error ("%<__thread%> used with %<auto%>");
      else if (specs->storage_class == csc_register)
	error ("%<__thread%> used with %<register%>");
      else if (specs->storage_class == csc_typedef)
	error ("%<__thread%> used with %<typedef%>");
      else
	specs->thread_p = true;
      break;
    case RID_AUTO:
      n = csc_auto;
      break;
    case RID_EXTERN:
      n = csc_extern;
      /* Diagnose "__thread extern".  */
      if (specs->thread_p)
	error ("%<__thread%> before %<extern%>");
      break;
    case RID_REGISTER:
      n = csc_register;
      break;
    case RID_STATIC:
      n = csc_static;
      /* Diagnose "__thread static".  */
      if (specs->thread_p)
	error ("%<__thread%> before %<static%>");
      break;
    case RID_TYPEDEF:
      n = csc_typedef;
      break;
    default:
      gcc_unreachable ();
    }
  if (n != csc_none && n == specs->storage_class)
    dupe = true;
  if (dupe)
    error ("duplicate %qE", scspec);
  if (n != csc_none)
    {
      if (specs->storage_class != csc_none && n != specs->storage_class)
	{
	  error ("multiple storage classes in declaration specifiers");
	}
      else
	{
	  specs->storage_class = n;
	  if (n != csc_extern && n != csc_static && specs->thread_p)
	    {
	      error ("%<__thread%> used with %qE", scspec);
	      specs->thread_p = false;
	    }
	}
    }
  return specs;
}