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

/* Variables and functions */
 scalar_t__ CLASSTYPE_VTABLES (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_METHODS (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_add_dllimport (scalar_t__) ; 

void
i386_pe_adjust_class_at_definition (tree t)
{
  tree member;

  gcc_assert (CLASS_TYPE_P (t));

 /* We only look at dllimport.  The only thing that dllexport does is
    add stuff to a '.drectiv' section at end-of-file, so no need to do
    anything for dllexport'd classes until we generate RTL. */  
  if (lookup_attribute ("dllimport", TYPE_ATTRIBUTES (t)) == NULL_TREE)
    return;

  /* We don't actually add the attribute to the decl, just set the flag
     that signals that the address of this symbol is not a compile-time
     constant.   Any subsequent out-of-class declaration of members wil
     cause the DECL_DLLIMPORT_P flag to be unset.
     (See  tree.c: merge_dllimport_decl_attributes).
     That is just right since out-of class declarations can only be a
     definition.  We recheck the class members  at RTL generation to
     emit warnings if this has happened.  Definition of static data member
     of dllimport'd class always causes an error (as per MS compiler).
     */

  /* Check static VAR_DECL's.  */
  for (member = TYPE_FIELDS (t); member; member = TREE_CHAIN (member))
    if (TREE_CODE (member) == VAR_DECL)     
      maybe_add_dllimport (member);
    
  /* Check FUNCTION_DECL's.  */
  for (member = TYPE_METHODS (t); member;  member = TREE_CHAIN (member))
    if (TREE_CODE (member) == FUNCTION_DECL)
      maybe_add_dllimport (member);
 
  /* Check vtables  */
  for (member = CLASSTYPE_VTABLES (t); member;  member = TREE_CHAIN (member))
    if (TREE_CODE (member) == VAR_DECL) 
      maybe_add_dllimport (member);

/* We leave typeinfo tables alone.  We can't mark TI objects as
     dllimport, since the address of a secondary VTT may be needed
     for static initialization of a primary VTT.  VTT's  of
     dllimport'd classes should always be link-once COMDAT.  */ 
}