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
typedef  scalar_t__ tree ;
struct cgraph_local_info {scalar_t__ local; } ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_SSE ; 
 scalar_t__ TARGET_SSE2 ; 
 scalar_t__ TARGET_SSEREGPARM ; 
 scalar_t__ TARGET_SSE_MATH ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 struct cgraph_local_info* cgraph_local_info (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ flag_unit_at_a_time ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_flag ; 

__attribute__((used)) static int
ix86_function_sseregparm (tree type, tree decl)
{
  /* Use SSE registers to pass SFmode and DFmode arguments if requested
     by the sseregparm attribute.  */
  if (TARGET_SSEREGPARM
      || (type
	  && lookup_attribute ("sseregparm", TYPE_ATTRIBUTES (type))))
    {
      if (!TARGET_SSE)
	{
	  if (decl)
	    error ("Calling %qD with attribute sseregparm without "
		   "SSE/SSE2 enabled", decl);
	  else
	    error ("Calling %qT with attribute sseregparm without "
		   "SSE/SSE2 enabled", type);
	  return 0;
	}

      return 2;
    }

  /* For local functions, pass up to SSE_REGPARM_MAX SFmode
     (and DFmode for SSE2) arguments in SSE registers,
     even for 32-bit targets.  */
  if (!TARGET_64BIT && decl
      && TARGET_SSE_MATH && flag_unit_at_a_time && !profile_flag)
    {
      struct cgraph_local_info *i = cgraph_local_info (decl);
      if (i && i->local)
	return TARGET_SSE2 ? 2 : 1;
    }

  return 0;
}