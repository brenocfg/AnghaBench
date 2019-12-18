#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* section; } ;
struct TYPE_10__ {TYPE_1__ indirect; } ;
struct bfd_link_order {scalar_t__ offset; scalar_t__ size; TYPE_2__ u; } ;
struct bfd_link_info {scalar_t__ relocatable; } ;
typedef  scalar_t__ file_ptr ;
typedef  int bfd_size_type ;
typedef  void bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {int flags; scalar_t__ size; scalar_t__ output_offset; int reloc_count; scalar_t__ rel_filepos; struct TYPE_11__* output_section; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_3__ asection ;
struct TYPE_12__ {int external_reloc_size; int /*<<< orphan*/  (* relocate_section ) (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_3__*,void*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_bread (void*,int,int /*<<< orphan*/ *) ; 
 int bfd_bwrite (void*,int,int /*<<< orphan*/ *) ; 
 void* bfd_malloc (int) ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_3__*,void**) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,TYPE_3__*,void*,scalar_t__,scalar_t__) ; 
 TYPE_6__* ecoff_backend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_3__*,void*,void*) ; 

__attribute__((used)) static bfd_boolean
ecoff_indirect_link_order (bfd *output_bfd,
			   struct bfd_link_info *info,
			   asection *output_section,
			   struct bfd_link_order *link_order)
{
  asection *input_section;
  bfd *input_bfd;
  bfd_byte *contents = NULL;
  bfd_size_type external_reloc_size;
  bfd_size_type external_relocs_size;
  void * external_relocs = NULL;

  BFD_ASSERT ((output_section->flags & SEC_HAS_CONTENTS) != 0);

  input_section = link_order->u.indirect.section;
  input_bfd = input_section->owner;
  if (input_section->size == 0)
    return TRUE;

  BFD_ASSERT (input_section->output_section == output_section);
  BFD_ASSERT (input_section->output_offset == link_order->offset);
  BFD_ASSERT (input_section->size == link_order->size);

  /* Get the section contents.  */
  if (!bfd_malloc_and_get_section (input_bfd, input_section, &contents))
    goto error_return;

  /* Get the relocs.  If we are relaxing MIPS code, they will already
     have been read in.  Otherwise, we read them in now.  */
  external_reloc_size = ecoff_backend (input_bfd)->external_reloc_size;
  external_relocs_size = external_reloc_size * input_section->reloc_count;

  external_relocs = bfd_malloc (external_relocs_size);
  if (external_relocs == NULL && external_relocs_size != 0)
    goto error_return;

  if (bfd_seek (input_bfd, input_section->rel_filepos, SEEK_SET) != 0
      || (bfd_bread (external_relocs, external_relocs_size, input_bfd)
	  != external_relocs_size))
    goto error_return;

  /* Relocate the section contents.  */
  if (! ((*ecoff_backend (input_bfd)->relocate_section)
	 (output_bfd, info, input_bfd, input_section, contents,
	  external_relocs)))
    goto error_return;

  /* Write out the relocated section.  */
  if (! bfd_set_section_contents (output_bfd,
				  output_section,
				  contents,
				  input_section->output_offset,
				  input_section->size))
    goto error_return;

  /* If we are producing relocatable output, the relocs were
     modified, and we write them out now.  We use the reloc_count
     field of output_section to keep track of the number of relocs we
     have output so far.  */
  if (info->relocatable)
    {
      file_ptr pos = (output_section->rel_filepos
		      + output_section->reloc_count * external_reloc_size);
      if (bfd_seek (output_bfd, pos, SEEK_SET) != 0
	  || (bfd_bwrite (external_relocs, external_relocs_size, output_bfd)
	      != external_relocs_size))
	goto error_return;
      output_section->reloc_count += input_section->reloc_count;
    }

  if (contents != NULL)
    free (contents);
  if (external_relocs != NULL)
    free (external_relocs);
  return TRUE;

 error_return:
  if (contents != NULL)
    free (contents);
  if (external_relocs != NULL)
    free (external_relocs);
  return FALSE;
}