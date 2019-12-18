#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct reloc_std_external {int dummy; } ;
struct reloc_ext_external {int dummy; } ;
struct bfd_link_info {int /*<<< orphan*/  keep_memory; } ;
struct aout_section_data_struct {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {int /*<<< orphan*/  rel_filepos; } ;
typedef  TYPE_1__ asection ;
struct TYPE_9__ {void* relocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RELOC_STD_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_6__* aout_section_data (TYPE_1__*) ; 
 struct aout_section_data_struct* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int bfd_bread (void*,int,int /*<<< orphan*/ *) ; 
 void* bfd_malloc (int) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ obj_reloc_entry_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_aout_section_data (TYPE_1__*,struct aout_section_data_struct*) ; 
 int /*<<< orphan*/  sunos_scan_ext_relocs (struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_1__*,struct reloc_ext_external*,int) ; 
 int /*<<< orphan*/  sunos_scan_std_relocs (struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_1__*,struct reloc_std_external*,int) ; 

__attribute__((used)) static bfd_boolean
sunos_scan_relocs (struct bfd_link_info *info,
		   bfd *abfd,
		   asection *sec,
		   bfd_size_type rel_size)
{
  void * relocs;
  void * free_relocs = NULL;

  if (rel_size == 0)
    return TRUE;

  if (! info->keep_memory)
    relocs = free_relocs = bfd_malloc (rel_size);
  else
    {
      struct aout_section_data_struct *n;
      bfd_size_type amt = sizeof (struct aout_section_data_struct);

      n = bfd_alloc (abfd, amt);
      if (n == NULL)
	relocs = NULL;
      else
	{
	  set_aout_section_data (sec, n);
	  relocs = bfd_malloc (rel_size);
	  aout_section_data (sec)->relocs = relocs;
	}
    }
  if (relocs == NULL)
    return FALSE;

  if (bfd_seek (abfd, sec->rel_filepos, SEEK_SET) != 0
      || bfd_bread (relocs, rel_size, abfd) != rel_size)
    goto error_return;

  if (obj_reloc_entry_size (abfd) == RELOC_STD_SIZE)
    {
      if (! sunos_scan_std_relocs (info, abfd, sec,
				   (struct reloc_std_external *) relocs,
				   rel_size))
	goto error_return;
    }
  else
    {
      if (! sunos_scan_ext_relocs (info, abfd, sec,
				   (struct reloc_ext_external *) relocs,
				   rel_size))
	goto error_return;
    }

  if (free_relocs != NULL)
    free (free_relocs);

  return TRUE;

 error_return:
  if (free_relocs != NULL)
    free (free_relocs);
  return FALSE;
}