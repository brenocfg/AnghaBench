#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {unsigned long ld_need; } ;
struct sunos_dynamic_info {int dynsym_count; char* dynstr; TYPE_2__ dyninfo; struct external_nlist* dynsym; } ;
struct external_nlist {int dummy; } ;
struct bfd_link_needed_list {char* name; struct bfd_link_needed_list* next; TYPE_3__* by; } ;
struct bfd_link_info {TYPE_1__* hash; scalar_t__ relocatable; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int bfd_size_type ;
typedef  char bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_24__ {scalar_t__ xvec; int flags; TYPE_4__* sections; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_25__ {int flags; struct TYPE_25__* next; } ;
typedef  TYPE_4__ asection ;
struct TYPE_26__ {struct bfd_link_needed_list* needed; TYPE_3__* dynobj; } ;
struct TYPE_22__ {scalar_t__ creator; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_LINKER_CREATED ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 void* bfd_alloc (TYPE_3__*,int) ; 
 int bfd_bread (char*,int,TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_get_16 (TYPE_3__*,char*) ; 
 unsigned long bfd_get_32 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (TYPE_3__*,char*) ; 
 TYPE_4__* bfd_make_section_with_flags (TYPE_3__*,char*,int) ; 
 char* bfd_malloc (int) ; 
 char* bfd_realloc (char*,int) ; 
 int /*<<< orphan*/  bfd_section_list_remove (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ bfd_seek (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ obj_aout_dynamic_info (TYPE_3__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  sunos_create_dynamic_sections (TYPE_3__*,struct bfd_link_info*,int) ; 
 TYPE_6__* sunos_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  sunos_slurp_dynamic_symtab (TYPE_3__*) ; 

__attribute__((used)) static bfd_boolean
sunos_add_dynamic_symbols (bfd *abfd,
			   struct bfd_link_info *info,
			   struct external_nlist **symsp,
			   bfd_size_type *sym_countp,
			   char **stringsp)
{
  bfd *dynobj;
  struct sunos_dynamic_info *dinfo;
  unsigned long need;

  /* Make sure we have all the required sections.  */
  if (info->hash->creator == abfd->xvec)
    {
      if (! sunos_create_dynamic_sections (abfd, info,
					   ((abfd->flags & DYNAMIC) != 0
					    && !info->relocatable)))
	return FALSE;
    }

  /* There is nothing else to do for a normal object.  */
  if ((abfd->flags & DYNAMIC) == 0)
    return TRUE;

  dynobj = sunos_hash_table (info)->dynobj;

  /* We do not want to include the sections in a dynamic object in the
     output file.  We hack by simply clobbering the list of sections
     in the BFD.  This could be handled more cleanly by, say, a new
     section flag; the existing SEC_NEVER_LOAD flag is not the one we
     want, because that one still implies that the section takes up
     space in the output file.  If this is the first object we have
     seen, we must preserve the dynamic sections we just created.  */
  if (abfd != dynobj)
    abfd->sections = NULL;
  else
    {
      asection *s;

      for (s = abfd->sections; s != NULL; s = s->next)
	{
	  if ((s->flags & SEC_LINKER_CREATED) == 0)
	    bfd_section_list_remove (abfd, s);
	}
    }

  /* The native linker seems to just ignore dynamic objects when -r is
     used.  */
  if (info->relocatable)
    return TRUE;

  /* There's no hope of using a dynamic object which does not exactly
     match the format of the output file.  */
  if (info->hash->creator != abfd->xvec)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  /* Make sure we have a .need and a .rules sections.  These are only
     needed if there really is a dynamic object in the link, so they
     are not added by sunos_create_dynamic_sections.  */
  if (bfd_get_section_by_name (dynobj, ".need") == NULL)
    {
      /* The .need section holds the list of names of shared objets
	 which must be included at runtime.  The address of this
	 section is put in the ld_need field.  */
      flagword flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS
			| SEC_IN_MEMORY | SEC_READONLY);
      asection *s = bfd_make_section_with_flags (dynobj, ".need", flags);
      if (s == NULL
	  || ! bfd_set_section_alignment (dynobj, s, 2))
	return FALSE;
    }

  if (bfd_get_section_by_name (dynobj, ".rules") == NULL)
    {
      /* The .rules section holds the path to search for shared
	 objects.  The address of this section is put in the ld_rules
	 field.  */
      flagword flags = (SEC_ALLOC | SEC_LOAD | SEC_HAS_CONTENTS
			| SEC_IN_MEMORY | SEC_READONLY);
      asection *s = bfd_make_section_with_flags (dynobj, ".rules", flags);
      if (s == NULL
	  || ! bfd_set_section_alignment (dynobj, s, 2))
	return FALSE;
    }

  /* Pick up the dynamic symbols and return them to the caller.  */
  if (! sunos_slurp_dynamic_symtab (abfd))
    return FALSE;

  dinfo = (struct sunos_dynamic_info *) obj_aout_dynamic_info (abfd);
  *symsp = dinfo->dynsym;
  *sym_countp = dinfo->dynsym_count;
  *stringsp = dinfo->dynstr;

  /* Record information about any other objects needed by this one.  */
  need = dinfo->dyninfo.ld_need;
  while (need != 0)
    {
      bfd_byte buf[16];
      unsigned long name, flags;
      unsigned short major_vno, minor_vno;
      struct bfd_link_needed_list *needed, **pp;
      char *namebuf, *p;
      bfd_size_type alc;
      bfd_byte b;
      char *namecopy;

      if (bfd_seek (abfd, (file_ptr) need, SEEK_SET) != 0
	  || bfd_bread (buf, (bfd_size_type) 16, abfd) != 16)
	return FALSE;

      /* For the format of an ld_need entry, see aout/sun4.h.  We
	 should probably define structs for this manipulation.  */
      name = bfd_get_32 (abfd, buf);
      flags = bfd_get_32 (abfd, buf + 4);
      major_vno = (unsigned short) bfd_get_16 (abfd, buf + 8);
      minor_vno = (unsigned short) bfd_get_16 (abfd, buf + 10);
      need = bfd_get_32 (abfd, buf + 12);

      alc = sizeof (struct bfd_link_needed_list);
      needed = bfd_alloc (abfd, alc);
      if (needed == NULL)
	return FALSE;
      needed->by = abfd;

      /* We return the name as [-l]name[.maj][.min].  */
      alc = 30;
      namebuf = bfd_malloc (alc + 1);
      if (namebuf == NULL)
	return FALSE;
      p = namebuf;

      if ((flags & 0x80000000) != 0)
	{
	  *p++ = '-';
	  *p++ = 'l';
	}
      if (bfd_seek (abfd, (file_ptr) name, SEEK_SET) != 0)
	{
	  free (namebuf);
	  return FALSE;
	}

      do
	{
	  if (bfd_bread (&b, (bfd_size_type) 1, abfd) != 1)
	    {
	      free (namebuf);
	      return FALSE;
	    }

	  if ((bfd_size_type) (p - namebuf) >= alc)
	    {
	      char *n;

	      alc *= 2;
	      n = bfd_realloc (namebuf, alc + 1);
	      if (n == NULL)
		{
		  free (namebuf);
		  return FALSE;
		}
	      p = n + (p - namebuf);
	      namebuf = n;
	    }

	  *p++ = b;
	}
      while (b != '\0');

      if (major_vno == 0)
	*p = '\0';
      else
	{
	  char majbuf[30];
	  char minbuf[30];

	  sprintf (majbuf, ".%d", major_vno);
	  if (minor_vno == 0)
	    minbuf[0] = '\0';
	  else
	    sprintf (minbuf, ".%d", minor_vno);

	  if ((p - namebuf) + strlen (majbuf) + strlen (minbuf) >= alc)
	    {
	      char *n;

	      alc = (p - namebuf) + strlen (majbuf) + strlen (minbuf);
	      n = bfd_realloc (namebuf, alc + 1);
	      if (n == NULL)
		{
		  free (namebuf);
		  return FALSE;
		}
	      p = n + (p - namebuf);
	      namebuf = n;
	    }

	  strcpy (p, majbuf);
	  strcat (p, minbuf);
	}

      namecopy = bfd_alloc (abfd, (bfd_size_type) strlen (namebuf) + 1);
      if (namecopy == NULL)
	{
	  free (namebuf);
	  return FALSE;
	}
      strcpy (namecopy, namebuf);
      free (namebuf);
      needed->name = namecopy;

      needed->next = NULL;

      for (pp = &sunos_hash_table (info)->needed;
	   *pp != NULL;
	   pp = &(*pp)->next)
	;
      *pp = needed;
    }

  return TRUE;
}