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
 scalar_t__ DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_THUNK_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ METHOD_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

bool
i386_pe_type_dllexport_p (tree decl)
{
   gcc_assert (TREE_CODE (decl) == VAR_DECL 
               || TREE_CODE (decl) == FUNCTION_DECL);
   /* Avoid exporting compiler-generated default dtors and copy ctors.
      The only artificial methods that need to be exported are virtual
      and non-virtual thunks.  */
   if (TREE_CODE (TREE_TYPE (decl)) == METHOD_TYPE
       && DECL_ARTIFICIAL (decl) && !DECL_THUNK_P (decl))
     return false;
   return true;
}