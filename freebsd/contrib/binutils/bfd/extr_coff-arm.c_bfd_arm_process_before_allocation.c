#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct internal_reloc {unsigned short r_type; long r_symndx; } ;
struct coff_link_hash_entry {int /*<<< orphan*/  class; } ;
struct coff_arm_link_hash_table {int support_old_code; int /*<<< orphan*/ * bfd_of_glue_owner; } ;
struct bfd_link_info {scalar_t__ relocatable; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_11__ {scalar_t__ reloc_count; struct TYPE_11__* next; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
#define  ARM_26 132 
#define  ARM_THUMB23 131 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
#define  C_EXT 130 
#define  C_LABEL 129 
#define  C_STAT 128 
 int /*<<< orphan*/  C_THUMBEXTFUNC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_coff_get_external_symbols (TYPE_1__*) ; 
 struct internal_reloc* _bfd_coff_read_internal_relocs (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_1__*,long) ; 
 struct coff_arm_link_hash_table* coff_arm_hash_table (struct bfd_link_info*) ; 
 struct coff_link_hash_entry** obj_coff_sym_hashes (TYPE_1__*) ; 
 long obj_conv_table_size (TYPE_1__*) ; 
 int /*<<< orphan*/  record_arm_to_thumb_glue (struct bfd_link_info*,struct coff_link_hash_entry*) ; 
 int /*<<< orphan*/  record_thumb_to_arm_glue (struct bfd_link_info*,struct coff_link_hash_entry*) ; 

bfd_boolean
bfd_arm_process_before_allocation (bfd *                   abfd,
				   struct bfd_link_info *  info,
				   int		           support_old_code)
{
  asection * sec;
  struct coff_arm_link_hash_table * globals;

  /* If we are only performing a partial link do not bother
     to construct any glue.  */
  if (info->relocatable)
    return TRUE;

  /* Here we have a bfd that is to be included on the link.  We have a hook
     to do reloc rummaging, before section sizes are nailed down.  */
  _bfd_coff_get_external_symbols (abfd);

  globals = coff_arm_hash_table (info);

  BFD_ASSERT (globals != NULL);
  BFD_ASSERT (globals->bfd_of_glue_owner != NULL);

  globals->support_old_code = support_old_code;

  /* Rummage around all the relocs and map the glue vectors.  */
  sec = abfd->sections;

  if (sec == NULL)
    return TRUE;

  for (; sec != NULL; sec = sec->next)
    {
      struct internal_reloc * i;
      struct internal_reloc * rel;

      if (sec->reloc_count == 0)
	continue;

      /* Load the relocs.  */
      /* FIXME: there may be a storage leak here.  */
      i = _bfd_coff_read_internal_relocs (abfd, sec, 1, 0, 0, 0);

      BFD_ASSERT (i != 0);

      for (rel = i; rel < i + sec->reloc_count; ++rel)
	{
	  unsigned short                 r_type  = rel->r_type;
	  long                           symndx;
	  struct coff_link_hash_entry *  h;

	  symndx = rel->r_symndx;

	  /* If the relocation is not against a symbol it cannot concern us.  */
	  if (symndx == -1)
	    continue;

	  /* If the index is outside of the range of our table, something has gone wrong.  */
	  if (symndx >= obj_conv_table_size (abfd))
	    {
	      _bfd_error_handler (_("%B: illegal symbol index in reloc: %d"),
				  abfd, symndx);
	      continue;
	    }

	  h = obj_coff_sym_hashes (abfd)[symndx];

	  /* If the relocation is against a static symbol it must be within
	     the current section and so cannot be a cross ARM/Thumb relocation.  */
	  if (h == NULL)
	    continue;

	  switch (r_type)
	    {
	    case ARM_26:
	      /* This one is a call from arm code.  We need to look up
		 the target of the call. If it is a thumb target, we
		 insert glue.  */

	      if (h->class == C_THUMBEXTFUNC)
		record_arm_to_thumb_glue (info, h);
	      break;

#ifndef ARM_WINCE
	    case ARM_THUMB23:
	      /* This one is a call from thumb code.  We used to look
		 for ARM_THUMB9 and ARM_THUMB12 as well.  We need to look
		 up the target of the call. If it is an arm target, we
		 insert glue.  If the symbol does not exist it will be
		 given a class of C_EXT and so we will generate a stub
		 for it.  This is not really a problem, since the link
		 is doomed anyway.  */

	      switch (h->class)
		{
		case C_EXT:
		case C_STAT:
		case C_LABEL:
		  record_thumb_to_arm_glue (info, h);
		  break;
		default:
		  ;
		}
	      break;
#endif

	    default:
	      break;
	    }
	}
    }

  return TRUE;
}