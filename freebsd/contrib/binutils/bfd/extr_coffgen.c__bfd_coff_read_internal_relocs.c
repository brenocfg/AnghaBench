#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct internal_reloc {int dummy; } ;
struct coff_section_tdata {int dummy; } ;
typedef  int bfd_size_type ;
typedef  struct internal_reloc bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int reloc_count; int /*<<< orphan*/ * used_by_bfd; int /*<<< orphan*/  rel_filepos; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {struct internal_reloc* relocs; int /*<<< orphan*/ * contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int bfd_bread (struct internal_reloc*,int,int /*<<< orphan*/ *) ; 
 int bfd_coff_relsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_coff_swap_reloc_in (int /*<<< orphan*/ *,void*,void*) ; 
 struct internal_reloc* bfd_malloc (int) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* coff_section_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  free (struct internal_reloc*) ; 
 int /*<<< orphan*/  memcpy (struct internal_reloc*,struct internal_reloc*,int) ; 

struct internal_reloc *
_bfd_coff_read_internal_relocs (bfd *abfd,
				asection *sec,
				bfd_boolean cache,
				bfd_byte *external_relocs,
				bfd_boolean require_internal,
				struct internal_reloc *internal_relocs)
{
  bfd_size_type relsz;
  bfd_byte *free_external = NULL;
  struct internal_reloc *free_internal = NULL;
  bfd_byte *erel;
  bfd_byte *erel_end;
  struct internal_reloc *irel;
  bfd_size_type amt;

  if (coff_section_data (abfd, sec) != NULL
      && coff_section_data (abfd, sec)->relocs != NULL)
    {
      if (! require_internal)
	return coff_section_data (abfd, sec)->relocs;
      memcpy (internal_relocs, coff_section_data (abfd, sec)->relocs,
	      sec->reloc_count * sizeof (struct internal_reloc));
      return internal_relocs;
    }

  relsz = bfd_coff_relsz (abfd);

  amt = sec->reloc_count * relsz;
  if (external_relocs == NULL)
    {
      free_external = bfd_malloc (amt);
      if (free_external == NULL && sec->reloc_count > 0)
	goto error_return;
      external_relocs = free_external;
    }

  if (bfd_seek (abfd, sec->rel_filepos, SEEK_SET) != 0
      || bfd_bread (external_relocs, amt, abfd) != amt)
    goto error_return;

  if (internal_relocs == NULL)
    {
      amt = sec->reloc_count;
      amt *= sizeof (struct internal_reloc);
      free_internal = bfd_malloc (amt);
      if (free_internal == NULL && sec->reloc_count > 0)
	goto error_return;
      internal_relocs = free_internal;
    }

  /* Swap in the relocs.  */
  erel = external_relocs;
  erel_end = erel + relsz * sec->reloc_count;
  irel = internal_relocs;
  for (; erel < erel_end; erel += relsz, irel++)
    bfd_coff_swap_reloc_in (abfd, (void *) erel, (void *) irel);

  if (free_external != NULL)
    {
      free (free_external);
      free_external = NULL;
    }

  if (cache && free_internal != NULL)
    {
      if (coff_section_data (abfd, sec) == NULL)
	{
	  amt = sizeof (struct coff_section_tdata);
	  sec->used_by_bfd = bfd_zalloc (abfd, amt);
	  if (sec->used_by_bfd == NULL)
	    goto error_return;
	  coff_section_data (abfd, sec)->contents = NULL;
	}
      coff_section_data (abfd, sec)->relocs = free_internal;
    }

  return internal_relocs;

 error_return:
  if (free_external != NULL)
    free (free_external);
  if (free_internal != NULL)
    free (free_internal);
  return NULL;
}