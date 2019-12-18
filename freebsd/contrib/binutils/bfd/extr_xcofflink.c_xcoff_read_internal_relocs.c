#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct internal_reloc {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {scalar_t__ reloc_count; size_t rel_filepos; } ;
typedef  TYPE_1__ asection ;
struct TYPE_10__ {struct internal_reloc* relocs; } ;
struct TYPE_9__ {TYPE_1__* enclosing; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 struct internal_reloc* _bfd_coff_read_internal_relocs (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,scalar_t__,struct internal_reloc*) ; 
 size_t bfd_coff_relsz (int /*<<< orphan*/ *) ; 
 TYPE_5__* coff_section_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (struct internal_reloc*,struct internal_reloc*,int) ; 
 TYPE_2__* xcoff_section_data (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static struct internal_reloc *
xcoff_read_internal_relocs (bfd *abfd,
			    asection *sec,
			    bfd_boolean cache,
			    bfd_byte *external_relocs,
			    bfd_boolean require_internal,
			    struct internal_reloc *internal_relocs)
{
  if (coff_section_data (abfd, sec) != NULL
      && coff_section_data (abfd, sec)->relocs == NULL
      && xcoff_section_data (abfd, sec) != NULL)
    {
      asection *enclosing;

      enclosing = xcoff_section_data (abfd, sec)->enclosing;

      if (enclosing != NULL
	  && (coff_section_data (abfd, enclosing) == NULL
	      || coff_section_data (abfd, enclosing)->relocs == NULL)
	  && cache
	  && enclosing->reloc_count > 0)
	{
	  if (_bfd_coff_read_internal_relocs (abfd, enclosing, TRUE,
					      external_relocs, FALSE, NULL)
	      == NULL)
	    return NULL;
	}

      if (enclosing != NULL
	  && coff_section_data (abfd, enclosing) != NULL
	  && coff_section_data (abfd, enclosing)->relocs != NULL)
	{
	  size_t off;

	  off = ((sec->rel_filepos - enclosing->rel_filepos)
		 / bfd_coff_relsz (abfd));

	  if (! require_internal)
	    return coff_section_data (abfd, enclosing)->relocs + off;
	  memcpy (internal_relocs,
		  coff_section_data (abfd, enclosing)->relocs + off,
		  sec->reloc_count * sizeof (struct internal_reloc));
	  return internal_relocs;
	}
    }

  return _bfd_coff_read_internal_relocs (abfd, sec, cache, external_relocs,
					 require_internal, internal_relocs);
}