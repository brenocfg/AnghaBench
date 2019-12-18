#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sec_merge_sec_info {TYPE_3__* sec; } ;
struct TYPE_5__ {char* string; } ;
struct sec_merge_hash_entry {int alignment; int len; TYPE_2__ root; struct sec_merge_hash_entry* next; struct sec_merge_sec_info* secinfo; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int size; TYPE_1__* output_section; } ;
typedef  TYPE_3__ asection ;
struct TYPE_4__ {int alignment_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_bwrite (char const*,int,int /*<<< orphan*/ *) ; 
 char* bfd_zmalloc (int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static bfd_boolean
sec_merge_emit (bfd *abfd, struct sec_merge_hash_entry *entry)
{
  struct sec_merge_sec_info *secinfo = entry->secinfo;
  asection *sec = secinfo->sec;
  char *pad = NULL;
  bfd_size_type off = 0;
  int alignment_power = sec->output_section->alignment_power;

  if (alignment_power)
    {
      pad = bfd_zmalloc ((bfd_size_type) 1 << alignment_power);
      if (pad == NULL)
	return FALSE;
    }

  for (; entry != NULL && entry->secinfo == secinfo; entry = entry->next)
    {
      const char *str;
      bfd_size_type len;

      len = -off & (entry->alignment - 1);
      if (len != 0)
	{
	  if (bfd_bwrite (pad, len, abfd) != len)
	    goto err;
	  off += len;
	}

      str = entry->root.string;
      len = entry->len;

      if (bfd_bwrite (str, len, abfd) != len)
	goto err;

      off += len;
    }

  /* Trailing alignment needed?  */
  off = sec->size - off;
  if (off != 0
      && bfd_bwrite (pad, off, abfd) != off)
    goto err;

  if (pad != NULL)
    free (pad);
  return TRUE;

 err:
  if (pad != NULL)
    free (pad);
  return FALSE;
}