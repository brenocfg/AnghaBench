#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sec_merge_sec_info {unsigned char* contents; int /*<<< orphan*/ ** psecinfo; struct sec_merge_sec_info* next; TYPE_1__* sec; } ;
struct sec_merge_info {struct sec_merge_sec_info* chain; int /*<<< orphan*/  htab; } ;
struct sec_merge_hash_entry {int /*<<< orphan*/  len; } ;
typedef  unsigned int bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {unsigned int alignment_power; int size; int flags; int entsize; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int SEC_STRINGS ; 
 scalar_t__ TRUE ; 
 struct sec_merge_hash_entry* sec_merge_add (int /*<<< orphan*/ ,char*,int,struct sec_merge_sec_info*) ; 

__attribute__((used)) static bfd_boolean
record_section (struct sec_merge_info *sinfo,
		struct sec_merge_sec_info *secinfo)
{
  asection *sec = secinfo->sec;
  struct sec_merge_hash_entry *entry;
  bfd_boolean nul;
  unsigned char *p, *end;
  bfd_vma mask, eltalign;
  unsigned int align, i;

  align = sec->alignment_power;
  end = secinfo->contents + sec->size;
  nul = FALSE;
  mask = ((bfd_vma) 1 << align) - 1;
  if (sec->flags & SEC_STRINGS)
    {
      for (p = secinfo->contents; p < end; )
	{
	  eltalign = p - secinfo->contents;
	  eltalign = ((eltalign ^ (eltalign - 1)) + 1) >> 1;
	  if (!eltalign || eltalign > mask)
	    eltalign = mask + 1;
	  entry = sec_merge_add (sinfo->htab, (char *) p, (unsigned) eltalign,
				 secinfo);
	  if (! entry)
	    goto error_return;
	  p += entry->len;
	  if (sec->entsize == 1)
	    {
	      while (p < end && *p == 0)
		{
		  if (!nul && !((p - secinfo->contents) & mask))
		    {
		      nul = TRUE;
		      entry = sec_merge_add (sinfo->htab, "",
					     (unsigned) mask + 1, secinfo);
		      if (! entry)
			goto error_return;
		    }
		  p++;
		}
	    }
	  else
	    {
	      while (p < end)
		{
		  for (i = 0; i < sec->entsize; i++)
		    if (p[i] != '\0')
		      break;
		  if (i != sec->entsize)
		    break;
		  if (!nul && !((p - secinfo->contents) & mask))
		    {
		      nul = TRUE;
		      entry = sec_merge_add (sinfo->htab, (char *) p,
					     (unsigned) mask + 1, secinfo);
		      if (! entry)
			goto error_return;
		    }
		  p += sec->entsize;
		}
	    }
	}
    }
  else
    {
      for (p = secinfo->contents; p < end; p += sec->entsize)
	{
	  entry = sec_merge_add (sinfo->htab, (char *) p, 1, secinfo);
	  if (! entry)
	    goto error_return;
	}
    }

  return TRUE;

error_return:
  for (secinfo = sinfo->chain; secinfo; secinfo = secinfo->next)
    *secinfo->psecinfo = NULL;
  return FALSE;
}