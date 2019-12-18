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
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ associated_type (int /*<<< orphan*/ ) ; 
 int i386_pe_type_dllexport_p (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
i386_pe_dllexport_p (tree decl)
{
  if (TREE_CODE (decl) != VAR_DECL
       && TREE_CODE (decl) != FUNCTION_DECL)
    return false;

  if (lookup_attribute ("dllexport", DECL_ATTRIBUTES (decl)))
    return true;

  /* Also mark class members of exported classes with dllexport.  */
  if (associated_type (decl)
      && lookup_attribute ("dllexport",
			    TYPE_ATTRIBUTES (associated_type (decl))))
    return i386_pe_type_dllexport_p (decl);

  return false;
}