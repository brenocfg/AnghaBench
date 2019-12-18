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
struct partial_die_info {int tag; int /*<<< orphan*/  is_declaration; int /*<<< orphan*/  highpc; int /*<<< orphan*/  lowpc; int /*<<< orphan*/  has_pc_info; int /*<<< orphan*/ * name; } ;
struct objfile {int /*<<< orphan*/ * obfd; } ;
struct dwarf2_cu {struct objfile* objfile; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
#define  DW_TAG_base_type 137 
#define  DW_TAG_class_type 136 
#define  DW_TAG_enumeration_type 135 
#define  DW_TAG_namespace 134 
#define  DW_TAG_structure_type 133 
#define  DW_TAG_subprogram 132 
#define  DW_TAG_subrange_type 131 
#define  DW_TAG_typedef 130 
#define  DW_TAG_union_type 129 
#define  DW_TAG_variable 128 
 char* add_partial_enumeration (struct partial_die_info*,char*,struct dwarf2_cu*,char const*) ; 
 char* add_partial_namespace (struct partial_die_info*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dwarf2_cu*,char const*) ; 
 char* add_partial_structure (struct partial_die_info*,char*,struct dwarf2_cu*,char const*) ; 
 int /*<<< orphan*/  add_partial_symbol (struct partial_die_info*,struct dwarf2_cu*,char const*) ; 
 char* locate_pdi_sibling (struct partial_die_info*,char*,int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 char* read_partial_die (struct partial_die_info*,int /*<<< orphan*/ *,char*,struct dwarf2_cu*) ; 

__attribute__((used)) static char *
scan_partial_symbols (char *info_ptr, CORE_ADDR *lowpc,
		      CORE_ADDR *highpc, struct dwarf2_cu *cu,
		      const char *namespace)
{
  struct objfile *objfile = cu->objfile;
  bfd *abfd = objfile->obfd;
  struct partial_die_info pdi;

  /* Now, march along the PDI's, descending into ones which have
     interesting children but skipping the children of the other ones,
     until we reach the end of the compilation unit.  */

  while (1)
    {
      /* This flag tells whether or not info_ptr has gotten updated
	 inside the loop.  */
      int info_ptr_updated = 0;

      info_ptr = read_partial_die (&pdi, abfd, info_ptr, cu);

      /* Anonymous namespaces have no name but have interesting
	 children, so we need to look at them.  Ditto for anonymous
	 enums.  */

      if (pdi.name != NULL || pdi.tag == DW_TAG_namespace
	  || pdi.tag == DW_TAG_enumeration_type)
	{
	  switch (pdi.tag)
	    {
	    case DW_TAG_subprogram:
	      if (pdi.has_pc_info)
		{
		  if (pdi.lowpc < *lowpc)
		    {
		      *lowpc = pdi.lowpc;
		    }
		  if (pdi.highpc > *highpc)
		    {
		      *highpc = pdi.highpc;
		    }
		  if (!pdi.is_declaration)
		    {
		      add_partial_symbol (&pdi, cu, namespace);
		    }
		}
	      break;
	    case DW_TAG_variable:
	    case DW_TAG_typedef:
	    case DW_TAG_union_type:
	      if (!pdi.is_declaration)
		{
		  add_partial_symbol (&pdi, cu, namespace);
		}
	      break;
	    case DW_TAG_class_type:
	    case DW_TAG_structure_type:
	      if (!pdi.is_declaration)
		{
		  info_ptr = add_partial_structure (&pdi, info_ptr, cu,
						    namespace);
		  info_ptr_updated = 1;
		}
	      break;
	    case DW_TAG_enumeration_type:
	      if (!pdi.is_declaration)
		{
		  info_ptr = add_partial_enumeration (&pdi, info_ptr, cu,
						      namespace);
		  info_ptr_updated = 1;
		}
	      break;
	    case DW_TAG_base_type:
            case DW_TAG_subrange_type:
	      /* File scope base type definitions are added to the partial
	         symbol table.  */
	      add_partial_symbol (&pdi, cu, namespace);
	      break;
	    case DW_TAG_namespace:
	      /* We've hit a DW_TAG_namespace entry, so we know this
		 file has been compiled using a compiler that
		 generates them; update NAMESPACE to reflect that.  */
	      if (namespace == NULL)
		namespace = "";
	      info_ptr = add_partial_namespace (&pdi, info_ptr, lowpc, highpc,
						cu, namespace);
	      info_ptr_updated = 1;
	      break;
	    default:
	      break;
	    }
	}

      if (pdi.tag == 0)
	break;

      /* If the die has a sibling, skip to the sibling, unless another
	 function has already updated info_ptr for us.  */

      /* NOTE: carlton/2003-06-16: This is a bit hackish, but whether
	 or not we want to update this depends on enough stuff (not
	 only pdi.tag but also whether or not pdi.name is NULL) that
	 this seems like the easiest way to handle the issue.  */

      if (!info_ptr_updated)
	info_ptr = locate_pdi_sibling (&pdi, info_ptr, abfd, cu);
    }

  return info_ptr;
}