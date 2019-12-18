#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sec_merge_sec_info {void** psecinfo; int /*<<< orphan*/  contents; int /*<<< orphan*/ * first_str; int /*<<< orphan*/ * htab; TYPE_2__* sec; struct sec_merge_sec_info* next; } ;
struct sec_merge_info {int /*<<< orphan*/ * htab; struct sec_merge_sec_info* chain; struct sec_merge_info* next; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_8__ {int flags; unsigned int entsize; unsigned int alignment_power; scalar_t__ output_section; int /*<<< orphan*/  size; int /*<<< orphan*/  owner; int /*<<< orphan*/  rawsize; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_EXCLUDE ; 
 int SEC_MERGE ; 
 int SEC_RELOC ; 
 int SEC_STRINGS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abort () ; 
 void* bfd_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sec_merge_init (unsigned int,int) ; 

bfd_boolean
_bfd_add_merge_section (bfd *abfd, void **psinfo, asection *sec,
			void **psecinfo)
{
  struct sec_merge_info *sinfo;
  struct sec_merge_sec_info *secinfo;
  unsigned int align;
  bfd_size_type amt;

  if ((abfd->flags & DYNAMIC) != 0
      || (sec->flags & SEC_MERGE) == 0)
    abort ();

  if (sec->size == 0
      || (sec->flags & SEC_EXCLUDE) != 0
      || sec->entsize == 0)
    return TRUE;

  if ((sec->flags & SEC_RELOC) != 0)
    {
      /* We aren't prepared to handle relocations in merged sections.  */
      return TRUE;
    }

  align = sec->alignment_power;
  if ((sec->entsize < (unsigned) 1 << align
       && ((sec->entsize & (sec->entsize - 1))
	   || !(sec->flags & SEC_STRINGS)))
      || (sec->entsize > (unsigned) 1 << align
	  && (sec->entsize & (((unsigned) 1 << align) - 1))))
    {
      /* Sanity check.  If string character size is smaller than
	 alignment, then we require character size to be a power
	 of 2, otherwise character size must be integer multiple
	 of alignment.  For non-string constants, alignment must
	 be smaller than or equal to entity size and entity size
	 must be integer multiple of alignment.  */
      return TRUE;
    }

  for (sinfo = (struct sec_merge_info *) *psinfo; sinfo; sinfo = sinfo->next)
    if ((secinfo = sinfo->chain)
	&& ! ((secinfo->sec->flags ^ sec->flags) & (SEC_MERGE | SEC_STRINGS))
	&& secinfo->sec->entsize == sec->entsize
	&& secinfo->sec->alignment_power == sec->alignment_power
	&& secinfo->sec->output_section == sec->output_section)
      break;

  if (sinfo == NULL)
    {
      /* Initialize the information we need to keep track of.  */
      sinfo = bfd_alloc (abfd, sizeof (struct sec_merge_info));
      if (sinfo == NULL)
	goto error_return;
      sinfo->next = (struct sec_merge_info *) *psinfo;
      sinfo->chain = NULL;
      *psinfo = sinfo;
      sinfo->htab = sec_merge_init (sec->entsize, (sec->flags & SEC_STRINGS));
      if (sinfo->htab == NULL)
	goto error_return;
    }

  /* Read the section from abfd.  */

  amt = sizeof (struct sec_merge_sec_info) + sec->size - 1;
  *psecinfo = bfd_alloc (abfd, amt);
  if (*psecinfo == NULL)
    goto error_return;

  secinfo = (struct sec_merge_sec_info *) *psecinfo;
  if (sinfo->chain)
    {
      secinfo->next = sinfo->chain->next;
      sinfo->chain->next = secinfo;
    }
  else
    secinfo->next = secinfo;
  sinfo->chain = secinfo;
  secinfo->sec = sec;
  secinfo->psecinfo = psecinfo;
  secinfo->htab = sinfo->htab;
  secinfo->first_str = NULL;

  sec->rawsize = sec->size;
  if (! bfd_get_section_contents (sec->owner, sec, secinfo->contents,
				  0, sec->size))
    goto error_return;

  return TRUE;

 error_return:
  *psecinfo = NULL;
  return FALSE;
}