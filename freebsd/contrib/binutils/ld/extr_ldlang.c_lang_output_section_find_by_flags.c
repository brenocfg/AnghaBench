#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; TYPE_3__* bfd_section; struct TYPE_13__* next; } ;
typedef  TYPE_2__ lang_output_section_statement_type ;
typedef  int /*<<< orphan*/  (* lang_match_sec_type_func ) (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__ const*) ;
typedef  int flagword ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  owner; } ;
typedef  TYPE_4__ asection ;
struct TYPE_16__ {TYPE_1__* head; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_12__ {TYPE_2__ output_section_statement; } ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_CODE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 int SEC_READONLY ; 
 int SEC_SMALL_DATA ; 
 int SEC_THREAD_LOCAL ; 
 TYPE_6__ lang_output_section_statement ; 
 int /*<<< orphan*/  output_bfd ; 

lang_output_section_statement_type *
lang_output_section_find_by_flags (const asection *sec,
				   lang_output_section_statement_type **exact,
				   lang_match_sec_type_func match_type)
{
  lang_output_section_statement_type *first, *look, *found;
  flagword flags;

  /* We know the first statement on this list is *ABS*.  May as well
     skip it.  */
  first = &lang_output_section_statement.head->output_section_statement;
  first = first->next;

  /* First try for an exact match.  */
  found = NULL;
  for (look = first; look; look = look->next)
    {
      flags = look->flags;
      if (look->bfd_section != NULL)
	{
	  flags = look->bfd_section->flags;
	  if (match_type && !match_type (output_bfd, look->bfd_section,
					 sec->owner, sec))
	    continue;
	}
      flags ^= sec->flags;
      if (!(flags & (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD | SEC_READONLY
		     | SEC_CODE | SEC_SMALL_DATA | SEC_THREAD_LOCAL)))
	found = look;
    }
  if (found != NULL)
    {
      if (exact != NULL)
	*exact = found;
      return found;
    }

  if (sec->flags & SEC_CODE)
    {
      /* Try for a rw code section.  */
      for (look = first; look; look = look->next)
	{
	  flags = look->flags;
	  if (look->bfd_section != NULL)
	    {
	      flags = look->bfd_section->flags;
	      if (match_type && !match_type (output_bfd, look->bfd_section,
					     sec->owner, sec))
		continue;
	    }
	  flags ^= sec->flags;
	  if (!(flags & (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD
			 | SEC_CODE | SEC_SMALL_DATA | SEC_THREAD_LOCAL)))
	    found = look;
	}
    }
  else if (sec->flags & (SEC_READONLY | SEC_THREAD_LOCAL))
    {
      /* .rodata can go after .text, .sdata2 after .rodata.  */
      for (look = first; look; look = look->next)
	{
	  flags = look->flags;
	  if (look->bfd_section != NULL)
	    {
	      flags = look->bfd_section->flags;
	      if (match_type && !match_type (output_bfd, look->bfd_section,
					     sec->owner, sec))
		continue;
	    }
	  flags ^= sec->flags;
	  if (!(flags & (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD
			 | SEC_READONLY))
	      && !(look->flags & (SEC_SMALL_DATA | SEC_THREAD_LOCAL)))
	    found = look;
	}
    }
  else if (sec->flags & SEC_SMALL_DATA)
    {
      /* .sdata goes after .data, .sbss after .sdata.  */
      for (look = first; look; look = look->next)
	{
	  flags = look->flags;
	  if (look->bfd_section != NULL)
	    {
	      flags = look->bfd_section->flags;
	      if (match_type && !match_type (output_bfd, look->bfd_section,
					     sec->owner, sec))
		continue;
	    }
	  flags ^= sec->flags;
	  if (!(flags & (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD
			 | SEC_THREAD_LOCAL))
	      || ((look->flags & SEC_SMALL_DATA)
		  && !(sec->flags & SEC_HAS_CONTENTS)))
	    found = look;
	}
    }
  else if (sec->flags & SEC_HAS_CONTENTS)
    {
      /* .data goes after .rodata.  */
      for (look = first; look; look = look->next)
	{
	  flags = look->flags;
	  if (look->bfd_section != NULL)
	    {
	      flags = look->bfd_section->flags;
	      if (match_type && !match_type (output_bfd, look->bfd_section,
					     sec->owner, sec))
		continue;
	    }
	  flags ^= sec->flags;
	  if (!(flags & (SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD
			 | SEC_SMALL_DATA | SEC_THREAD_LOCAL)))
	    found = look;
	}
    }
  else
    {
      /* .bss goes last.  */
      for (look = first; look; look = look->next)
	{
	  flags = look->flags;
	  if (look->bfd_section != NULL)
	    {
	      flags = look->bfd_section->flags;
	      if (match_type && !match_type (output_bfd, look->bfd_section,
					     sec->owner, sec))
		continue;
	    }
	  flags ^= sec->flags;
	  if (!(flags & SEC_ALLOC))
	    found = look;
	}
    }

  if (found || !match_type)
    return found;

  return lang_output_section_find_by_flags (sec, NULL, NULL);
}