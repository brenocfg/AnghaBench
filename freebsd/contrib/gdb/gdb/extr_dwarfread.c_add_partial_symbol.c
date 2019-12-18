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
struct objfile {int /*<<< orphan*/  static_psymbols; int /*<<< orphan*/  global_psymbols; } ;
struct dieinfo {int die_tag; int /*<<< orphan*/  at_name; int /*<<< orphan*/  has_at_byte_size; int /*<<< orphan*/  at_low_pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOC_BLOCK ; 
 int /*<<< orphan*/  LOC_STATIC ; 
 int /*<<< orphan*/  LOC_TYPEDEF ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
#define  TAG_class_type 136 
#define  TAG_enumeration_type 135 
#define  TAG_global_subroutine 134 
#define  TAG_global_variable 133 
#define  TAG_local_variable 132 
#define  TAG_structure_type 131 
#define  TAG_subroutine 130 
#define  TAG_typedef 129 
#define  TAG_union_type 128 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  add_psymbol_to_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct objfile*) ; 
 int /*<<< orphan*/  cu_language ; 
 int /*<<< orphan*/  language_cplus ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_partial_symbol (struct dieinfo *dip, struct objfile *objfile)
{
  switch (dip->die_tag)
    {
    case TAG_global_subroutine:
      add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			   VAR_DOMAIN, LOC_BLOCK,
			   &objfile->global_psymbols,
			   0, dip->at_low_pc, cu_language, objfile);
      break;
    case TAG_global_variable:
      add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			   VAR_DOMAIN, LOC_STATIC,
			   &objfile->global_psymbols,
			   0, 0, cu_language, objfile);
      break;
    case TAG_subroutine:
      add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			   VAR_DOMAIN, LOC_BLOCK,
			   &objfile->static_psymbols,
			   0, dip->at_low_pc, cu_language, objfile);
      break;
    case TAG_local_variable:
      add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			   VAR_DOMAIN, LOC_STATIC,
			   &objfile->static_psymbols,
			   0, 0, cu_language, objfile);
      break;
    case TAG_typedef:
      add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			   VAR_DOMAIN, LOC_TYPEDEF,
			   &objfile->static_psymbols,
			   0, 0, cu_language, objfile);
      break;
    case TAG_class_type:
    case TAG_structure_type:
    case TAG_union_type:
    case TAG_enumeration_type:
      /* Do not add opaque aggregate definitions to the psymtab.  */
      if (!dip->has_at_byte_size)
	break;
      add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			   STRUCT_DOMAIN, LOC_TYPEDEF,
			   &objfile->static_psymbols,
			   0, 0, cu_language, objfile);
      if (cu_language == language_cplus)
	{
	  /* For C++, these implicitly act as typedefs as well. */
	  add_psymbol_to_list (dip->at_name, strlen (dip->at_name),
			       VAR_DOMAIN, LOC_TYPEDEF,
			       &objfile->static_psymbols,
			       0, 0, cu_language, objfile);
	}
      break;
    }
}