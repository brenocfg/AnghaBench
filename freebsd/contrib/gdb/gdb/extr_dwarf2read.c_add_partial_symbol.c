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
struct partial_symbol {int dummy; } ;
struct partial_die_info {char* name; int tag; int /*<<< orphan*/  has_children; int /*<<< orphan*/ * locdesc; int /*<<< orphan*/  has_type; int /*<<< orphan*/  is_external; scalar_t__ lowpc; } ;
struct objfile {int /*<<< orphan*/  static_psymbols; int /*<<< orphan*/  global_psymbols; int /*<<< orphan*/  section_offsets; } ;
struct dwarf2_cu {scalar_t__ language; struct objfile* objfile; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DW_TAG_base_type 137 
#define  DW_TAG_class_type 136 
#define  DW_TAG_enumeration_type 135 
#define  DW_TAG_enumerator 134 
#define  DW_TAG_structure_type 133 
#define  DW_TAG_subprogram 132 
#define  DW_TAG_subrange_type 131 
#define  DW_TAG_typedef 130 
#define  DW_TAG_union_type 129 
#define  DW_TAG_variable 128 
 int /*<<< orphan*/  LOC_BLOCK ; 
 int /*<<< orphan*/  LOC_CONST ; 
 int /*<<< orphan*/  LOC_STATIC ; 
 int /*<<< orphan*/  LOC_TYPEDEF ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 int /*<<< orphan*/ * SYMBOL_CPLUS_DEMANGLED_NAME (struct partial_symbol const*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct partial_symbol* add_psymbol_to_list (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct objfile*) ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  cp_check_possible_namespace_symbols (int /*<<< orphan*/ *,struct objfile*) ; 
 scalar_t__ decode_locdesc (int /*<<< orphan*/ *,struct dwarf2_cu*) ; 
 scalar_t__ language_cplus ; 
 scalar_t__ pdi_needs_namespace (int,char const*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
add_partial_symbol (struct partial_die_info *pdi,
		    struct dwarf2_cu *cu, const char *namespace)
{
  struct objfile *objfile = cu->objfile;
  CORE_ADDR addr = 0;
  char *actual_name = pdi->name;
  const struct partial_symbol *psym = NULL;
  CORE_ADDR baseaddr;

  baseaddr = ANOFFSET (objfile->section_offsets, SECT_OFF_TEXT (objfile));

  /* If we're not in the global namespace and if the namespace name
     isn't encoded in a mangled actual_name, add it.  */
  
  if (pdi_needs_namespace (pdi->tag, namespace))
    {
      actual_name = alloca (strlen (pdi->name) + 2 + strlen (namespace) + 1);
      strcpy (actual_name, namespace);
      strcat (actual_name, "::");
      strcat (actual_name, pdi->name);
    }

  switch (pdi->tag)
    {
    case DW_TAG_subprogram:
      if (pdi->is_external)
	{
	  /*prim_record_minimal_symbol (actual_name, pdi->lowpc + baseaddr,
	     mst_text, objfile); */
	  psym = add_psymbol_to_list (actual_name, strlen (actual_name),
				      VAR_DOMAIN, LOC_BLOCK,
				      &objfile->global_psymbols,
				      0, pdi->lowpc + baseaddr,
				      cu->language, objfile);
	}
      else
	{
	  /*prim_record_minimal_symbol (actual_name, pdi->lowpc + baseaddr,
	     mst_file_text, objfile); */
	  psym = add_psymbol_to_list (actual_name, strlen (actual_name),
				      VAR_DOMAIN, LOC_BLOCK,
				      &objfile->static_psymbols,
				      0, pdi->lowpc + baseaddr,
				      cu->language, objfile);
	}
      break;
    case DW_TAG_variable:
      if (pdi->is_external)
	{
	  /* Global Variable.
	     Don't enter into the minimal symbol tables as there is
	     a minimal symbol table entry from the ELF symbols already.
	     Enter into partial symbol table if it has a location
	     descriptor or a type.
	     If the location descriptor is missing, new_symbol will create
	     a LOC_UNRESOLVED symbol, the address of the variable will then
	     be determined from the minimal symbol table whenever the variable
	     is referenced.
	     The address for the partial symbol table entry is not
	     used by GDB, but it comes in handy for debugging partial symbol
	     table building.  */

	  if (pdi->locdesc)
	    addr = decode_locdesc (pdi->locdesc, cu);
	  if (pdi->locdesc || pdi->has_type)
	    psym = add_psymbol_to_list (actual_name, strlen (actual_name),
					VAR_DOMAIN, LOC_STATIC,
					&objfile->global_psymbols,
					0, addr + baseaddr,
					cu->language, objfile);
	}
      else
	{
	  /* Static Variable. Skip symbols without location descriptors.  */
	  if (pdi->locdesc == NULL)
	    return;
	  addr = decode_locdesc (pdi->locdesc, cu);
	  /*prim_record_minimal_symbol (actual_name, addr + baseaddr,
	     mst_file_data, objfile); */
	  psym = add_psymbol_to_list (actual_name, strlen (actual_name),
				      VAR_DOMAIN, LOC_STATIC,
				      &objfile->static_psymbols,
				      0, addr + baseaddr,
				      cu->language, objfile);
	}
      break;
    case DW_TAG_typedef:
    case DW_TAG_base_type:
    case DW_TAG_subrange_type:
      add_psymbol_to_list (actual_name, strlen (actual_name),
			   VAR_DOMAIN, LOC_TYPEDEF,
			   &objfile->static_psymbols,
			   0, (CORE_ADDR) 0, cu->language, objfile);
      break;
    case DW_TAG_class_type:
    case DW_TAG_structure_type:
    case DW_TAG_union_type:
    case DW_TAG_enumeration_type:
      /* Skip aggregate types without children, these are external
         references.  */
      /* NOTE: carlton/2003-10-07: See comment in new_symbol about
	 static vs. global.  */
      if (pdi->has_children == 0)
	return;
      add_psymbol_to_list (actual_name, strlen (actual_name),
			   STRUCT_DOMAIN, LOC_TYPEDEF,
			   cu->language == language_cplus
			   ? &objfile->global_psymbols
			   : &objfile->static_psymbols,
			   0, (CORE_ADDR) 0, cu->language, objfile);

      if (cu->language == language_cplus)
	{
	  /* For C++, these implicitly act as typedefs as well. */
	  add_psymbol_to_list (actual_name, strlen (actual_name),
			       VAR_DOMAIN, LOC_TYPEDEF,
			       &objfile->global_psymbols,
			       0, (CORE_ADDR) 0, cu->language, objfile);
	}
      break;
    case DW_TAG_enumerator:
      add_psymbol_to_list (actual_name, strlen (actual_name),
			   VAR_DOMAIN, LOC_CONST,
			   cu->language == language_cplus
			   ? &objfile->global_psymbols
			   : &objfile->static_psymbols,
			   0, (CORE_ADDR) 0, cu->language, objfile);
      break;
    default:
      break;
    }

  /* Check to see if we should scan the name for possible namespace
     info.  Only do this if this is C++, if we don't have namespace
     debugging info in the file, if the psym is of an appropriate type
     (otherwise we'll have psym == NULL), and if we actually had a
     mangled name to begin with.  */

  if (cu->language == language_cplus
      && namespace == NULL
      && psym != NULL
      && SYMBOL_CPLUS_DEMANGLED_NAME (psym) != NULL)
    cp_check_possible_namespace_symbols (SYMBOL_CPLUS_DEMANGLED_NAME (psym),
					 objfile);
}