#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct partial_die_info {char* name; scalar_t__ tag; scalar_t__ has_children; } ;
struct dwarf2_cu {scalar_t__ language; TYPE_1__* objfile; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/ * obfd; } ;

/* Variables and functions */
 scalar_t__ DW_TAG_subprogram ; 
 int /*<<< orphan*/  add_partial_symbol (struct partial_die_info*,struct dwarf2_cu*,char const*) ; 
 char* class_name_from_physname (char*) ; 
 scalar_t__ language_cplus ; 
 char* locate_pdi_sibling (struct partial_die_info*,char*,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 char* read_partial_die (struct partial_die_info*,int /*<<< orphan*/ *,char*,struct dwarf2_cu*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static char *
add_partial_structure (struct partial_die_info *struct_pdi, char *info_ptr,
		       struct dwarf2_cu *cu,
		       const char *namespace)
{
  bfd *abfd = cu->objfile->obfd;
  char *actual_class_name = NULL;

  if (cu->language == language_cplus
      && (namespace == NULL || namespace[0] == '\0')
      && struct_pdi->name != NULL
      && struct_pdi->has_children)
    {
      /* See if we can figure out if the class lives in a namespace
	 (or is nested within another class.)  We do this by looking
	 for a member function; its demangled name will contain
	 namespace info, if there is any.  */

      /* NOTE: carlton/2003-10-07: Getting the info this way changes
	 what template types look like, because the demangler
	 frequently doesn't give the same name as the debug info.  We
	 could fix this by only using the demangled name to get the
	 prefix (but see comment in read_structure_type).  */

      /* FIXME: carlton/2004-01-23: If NAMESPACE equals "", we have
	 the appropriate debug information, so it would be nice to be
	 able to avoid this hack.  But NAMESPACE may not be the
	 namespace where this class was defined: NAMESPACE reflects
	 where STRUCT_PDI occurs in the tree of dies, but because of
	 DW_AT_specification, that may not actually tell us where the
	 class is defined.  (See the comment in read_func_scope for an
	 example of how this could occur.)

         Unfortunately, our current partial symtab data structures are
         completely unable to deal with DW_AT_specification.  So, for
         now, the best thing to do is to get nesting information from
         places other than the tree structure of dies if there's any
         chance that a DW_AT_specification is involved. :-( */

      char *next_child = info_ptr;

      while (1)
	{
	  struct partial_die_info child_pdi;

	  next_child = read_partial_die (&child_pdi, abfd, next_child,
					 cu);
	  if (!child_pdi.tag)
	    break;
	  if (child_pdi.tag == DW_TAG_subprogram)
	    {
	      actual_class_name = class_name_from_physname (child_pdi.name);
	      if (actual_class_name != NULL)
		struct_pdi->name = actual_class_name;
	      break;
	    }
	  else
	    {
	      next_child = locate_pdi_sibling (&child_pdi, next_child,
					       abfd, cu);
	    }
	}
    }

  add_partial_symbol (struct_pdi, cu, namespace);
  xfree (actual_class_name);

  return locate_pdi_sibling (struct_pdi, info_ptr, abfd, cu);
}