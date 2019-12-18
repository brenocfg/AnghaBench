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
typedef  scalar_t__ htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ DECL_ONE_ONLY (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  INSERT ; 
 unsigned int SECTION_CODE ; 
 unsigned int SECTION_LINKONCE ; 
 unsigned int SECTION_PE_SHARED ; 
 unsigned int SECTION_WRITE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ decl_readonly_section (scalar_t__,int) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 scalar_t__ htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_eq_pointer ; 
 scalar_t__ htab_find_slot (scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (int) ; 

unsigned int
i386_pe_section_type_flags (tree decl, const char *name, int reloc)
{
  static htab_t htab;
  unsigned int flags;
  unsigned int **slot;

  /* The names we put in the hashtable will always be the unique
     versions given to us by the stringtable, so we can just use
     their addresses as the keys.  */
  if (!htab)
    htab = htab_create (31, htab_hash_pointer, htab_eq_pointer, NULL);

  if (decl && TREE_CODE (decl) == FUNCTION_DECL)
    flags = SECTION_CODE;
  else if (decl && decl_readonly_section (decl, reloc))
    flags = 0;
  else
    {
      flags = SECTION_WRITE;

      if (decl && TREE_CODE (decl) == VAR_DECL
	  && lookup_attribute ("shared", DECL_ATTRIBUTES (decl)))
	flags |= SECTION_PE_SHARED;
    }

  if (decl && DECL_ONE_ONLY (decl))
    flags |= SECTION_LINKONCE;

  /* See if we already have an entry for this section.  */
  slot = (unsigned int **) htab_find_slot (htab, name, INSERT);
  if (!*slot)
    {
      *slot = (unsigned int *) xmalloc (sizeof (unsigned int));
      **slot = flags;
    }
  else
    {
      if (decl && **slot != flags)
	error ("%q+D causes a section type conflict", decl);
    }

  return flags;
}