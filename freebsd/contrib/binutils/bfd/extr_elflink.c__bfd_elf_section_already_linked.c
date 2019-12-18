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
struct bfd_section_already_linked_hash_entry {struct bfd_section_already_linked* entry; } ;
struct bfd_section_already_linked {struct bfd_section* sec; struct bfd_section_already_linked* next; } ;
struct bfd_section {scalar_t__ output_section; int flags; struct bfd_section* kept_section; int /*<<< orphan*/ * owner; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;
struct bfd_link_info {int dummy; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
typedef  struct bfd_section asection ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int SEC_GROUP ; 
 int SEC_LINK_DUPLICATES ; 
#define  SEC_LINK_DUPLICATES_DISCARD 131 
#define  SEC_LINK_DUPLICATES_ONE_ONLY 130 
#define  SEC_LINK_DUPLICATES_SAME_CONTENTS 129 
#define  SEC_LINK_DUPLICATES_SAME_SIZE 128 
 int SEC_LINK_ONCE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_abs_section_ptr ; 
 int /*<<< orphan*/ * bfd_coff_get_comdat_section (int /*<<< orphan*/ *,struct bfd_section*) ; 
 scalar_t__ bfd_elf_match_symbols_in_sections (struct bfd_section*,struct bfd_section*,struct bfd_link_info*) ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,struct bfd_section*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_section_already_linked_table_insert (struct bfd_section_already_linked_hash_entry*,struct bfd_section*) ; 
 struct bfd_section_already_linked_hash_entry* bfd_section_already_linked_table_lookup (char const*) ; 
 struct bfd_section* elf_next_in_group (struct bfd_section*) ; 
 int /*<<< orphan*/ * elf_sec_group (struct bfd_section*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bfd_section*) ; 

void
_bfd_elf_section_already_linked (bfd *abfd, struct bfd_section *sec,
				 struct bfd_link_info *info)
{
  flagword flags;
  const char *name, *p;
  struct bfd_section_already_linked *l;
  struct bfd_section_already_linked_hash_entry *already_linked_list;

  if (sec->output_section == bfd_abs_section_ptr)
    return;

  flags = sec->flags;

  /* Return if it isn't a linkonce section.  A comdat group section
     also has SEC_LINK_ONCE set.  */
  if ((flags & SEC_LINK_ONCE) == 0)
    return;

  /* Don't put group member sections on our list of already linked
     sections.  They are handled as a group via their group section.  */
  if (elf_sec_group (sec) != NULL)
    return;

  /* FIXME: When doing a relocatable link, we may have trouble
     copying relocations in other sections that refer to local symbols
     in the section being discarded.  Those relocations will have to
     be converted somehow; as of this writing I'm not sure that any of
     the backends handle that correctly.

     It is tempting to instead not discard link once sections when
     doing a relocatable link (technically, they should be discarded
     whenever we are building constructors).  However, that fails,
     because the linker winds up combining all the link once sections
     into a single large link once section, which defeats the purpose
     of having link once sections in the first place.

     Also, not merging link once sections in a relocatable link
     causes trouble for MIPS ELF, which relies on link once semantics
     to handle the .reginfo section correctly.  */

  name = bfd_get_section_name (abfd, sec);

  if (CONST_STRNEQ (name, ".gnu.linkonce.")
      && (p = strchr (name + sizeof (".gnu.linkonce.") - 1, '.')) != NULL)
    p++;
  else
    p = name;

  already_linked_list = bfd_section_already_linked_table_lookup (p);

  for (l = already_linked_list->entry; l != NULL; l = l->next)
    {
      /* We may have 2 different types of sections on the list: group
	 sections and linkonce sections.  Match like sections.  */
      if ((flags & SEC_GROUP) == (l->sec->flags & SEC_GROUP)
	  && strcmp (name, l->sec->name) == 0
	  && bfd_coff_get_comdat_section (l->sec->owner, l->sec) == NULL)
	{
	  /* The section has already been linked.  See if we should
	     issue a warning.  */
	  switch (flags & SEC_LINK_DUPLICATES)
	    {
	    default:
	      abort ();

	    case SEC_LINK_DUPLICATES_DISCARD:
	      break;

	    case SEC_LINK_DUPLICATES_ONE_ONLY:
	      (*_bfd_error_handler)
		(_("%B: ignoring duplicate section `%A'"),
		 abfd, sec);
	      break;

	    case SEC_LINK_DUPLICATES_SAME_SIZE:
	      if (sec->size != l->sec->size)
		(*_bfd_error_handler)
		  (_("%B: duplicate section `%A' has different size"),
		   abfd, sec);
	      break;

	    case SEC_LINK_DUPLICATES_SAME_CONTENTS:
	      if (sec->size != l->sec->size)
		(*_bfd_error_handler)
		  (_("%B: duplicate section `%A' has different size"),
		   abfd, sec);
	      else if (sec->size != 0)
		{
		  bfd_byte *sec_contents, *l_sec_contents = NULL;

		  if (!bfd_malloc_and_get_section (abfd, sec, &sec_contents))
		    (*_bfd_error_handler)
		      (_("%B: warning: could not read contents of section `%A'"),
		       abfd, sec);
		  else if (!bfd_malloc_and_get_section (l->sec->owner, l->sec,
							&l_sec_contents))
		    (*_bfd_error_handler)
		      (_("%B: warning: could not read contents of section `%A'"),
		       l->sec->owner, l->sec);
		  else if (memcmp (sec_contents, l_sec_contents, sec->size) != 0)
		    (*_bfd_error_handler)
		      (_("%B: warning: duplicate section `%A' has different contents"),
		       abfd, sec);

		  if (sec_contents)
		    free (sec_contents);
		  if (l_sec_contents)
		    free (l_sec_contents);
		}
	      break;
	    }

	  /* Set the output_section field so that lang_add_section
	     does not create a lang_input_section structure for this
	     section.  Since there might be a symbol in the section
	     being discarded, we must retain a pointer to the section
	     which we are really going to use.  */
	  sec->output_section = bfd_abs_section_ptr;
	  sec->kept_section = l->sec;

	  if (flags & SEC_GROUP)
	    {
	      asection *first = elf_next_in_group (sec);
	      asection *s = first;

	      while (s != NULL)
		{
		  s->output_section = bfd_abs_section_ptr;
		  /* Record which group discards it.  */
		  s->kept_section = l->sec;
		  s = elf_next_in_group (s);
		  /* These lists are circular.  */
		  if (s == first)
		    break;
		}
	    }

	  return;
	}
    }

  /* A single member comdat group section may be discarded by a
     linkonce section and vice versa.  */

  if ((flags & SEC_GROUP) != 0)
    {
      asection *first = elf_next_in_group (sec);

      if (first != NULL && elf_next_in_group (first) == first)
	/* Check this single member group against linkonce sections.  */
	for (l = already_linked_list->entry; l != NULL; l = l->next)
	  if ((l->sec->flags & SEC_GROUP) == 0
	      && bfd_coff_get_comdat_section (l->sec->owner, l->sec) == NULL
	      && bfd_elf_match_symbols_in_sections (l->sec, first, info))
	    {
	      first->output_section = bfd_abs_section_ptr;
	      first->kept_section = l->sec;
	      sec->output_section = bfd_abs_section_ptr;
	      break;
	    }
    }
  else
    /* Check this linkonce section against single member groups.  */
    for (l = already_linked_list->entry; l != NULL; l = l->next)
      if (l->sec->flags & SEC_GROUP)
	{
	  asection *first = elf_next_in_group (l->sec);

	  if (first != NULL
	      && elf_next_in_group (first) == first
	      && bfd_elf_match_symbols_in_sections (first, sec, info))
	    {
	      sec->output_section = bfd_abs_section_ptr;
	      sec->kept_section = first;
	      break;
	    }
	}

  /* This is the first section with this name.  Record it.  */
  bfd_section_already_linked_table_insert (already_linked_list, sec);
}