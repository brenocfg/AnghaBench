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
struct sec_merge_sec_info {TYPE_1__* sec; struct sec_merge_hash_entry* first_str; } ;
struct sec_merge_info {TYPE_2__* htab; } ;
struct TYPE_6__ {int index; struct sec_merge_hash_entry* suffix; } ;
struct sec_merge_hash_entry {int alignment; int len; TYPE_3__ u; struct sec_merge_sec_info* secinfo; struct sec_merge_hash_entry* next; } ;
typedef  int bfd_vma ;
typedef  int bfd_size_type ;
struct TYPE_5__ {int size; unsigned int entsize; struct sec_merge_hash_entry* first; } ;
struct TYPE_4__ {int size; int alignment_power; } ;

/* Variables and functions */
 struct sec_merge_hash_entry** bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct sec_merge_hash_entry**) ; 
 scalar_t__ is_suffix (struct sec_merge_hash_entry*,struct sec_merge_hash_entry*) ; 
 int /*<<< orphan*/  qsort (struct sec_merge_hash_entry**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strrevcmp ; 
 int /*<<< orphan*/  strrevcmp_align ; 

__attribute__((used)) static void
merge_strings (struct sec_merge_info *sinfo)
{
  struct sec_merge_hash_entry **array, **a, *e;
  struct sec_merge_sec_info *secinfo;
  bfd_size_type size, amt;
  unsigned int alignment = 0;

  /* Now sort the strings */
  amt = sinfo->htab->size * sizeof (struct sec_merge_hash_entry *);
  array = bfd_malloc (amt);
  if (array == NULL)
    goto alloc_failure;

  for (e = sinfo->htab->first, a = array; e; e = e->next)
    if (e->alignment)
      {
	*a++ = e;
	/* Adjust the length to not include the zero terminator.  */
	e->len -= sinfo->htab->entsize;
	if (alignment != e->alignment)
	  {
	    if (alignment == 0)
	      alignment = e->alignment;
	    else
	      alignment = (unsigned) -1;
	  }
      }

  sinfo->htab->size = a - array;
  if (sinfo->htab->size != 0)
    {
      qsort (array, (size_t) sinfo->htab->size,
	     sizeof (struct sec_merge_hash_entry *),
	     (alignment != (unsigned) -1 && alignment > sinfo->htab->entsize
	      ? strrevcmp_align : strrevcmp));

      /* Loop over the sorted array and merge suffixes */
      e = *--a;
      e->len += sinfo->htab->entsize;
      while (--a >= array)
	{
	  struct sec_merge_hash_entry *cmp = *a;

	  cmp->len += sinfo->htab->entsize;
	  if (e->alignment >= cmp->alignment
	      && !((e->len - cmp->len) & (cmp->alignment - 1))
	      && is_suffix (e, cmp))
	    {
	      cmp->u.suffix = e;
	      cmp->alignment = 0;
	    }
	  else
	    e = cmp;
	}
    }

alloc_failure:
  if (array)
    free (array);

  /* Now assign positions to the strings we want to keep.  */
  size = 0;
  secinfo = sinfo->htab->first->secinfo;
  for (e = sinfo->htab->first; e; e = e->next)
    {
      if (e->secinfo != secinfo)
	{
	  secinfo->sec->size = size;
	  secinfo = e->secinfo;
	}
      if (e->alignment)
	{
	  if (e->secinfo->first_str == NULL)
	    {
	      e->secinfo->first_str = e;
	      size = 0;
	    }
	  size = (size + e->alignment - 1) & ~((bfd_vma) e->alignment - 1);
	  e->u.index = size;
	  size += e->len;
	}
    }
  secinfo->sec->size = size;
  if (secinfo->sec->alignment_power != 0)
    {
      bfd_size_type align = (bfd_size_type) 1 << secinfo->sec->alignment_power;
      secinfo->sec->size = (secinfo->sec->size + align - 1) & -align;
    }

  /* And now adjust the rest, removing them from the chain (but not hashtable)
     at the same time.  */
  for (a = &sinfo->htab->first, e = *a; e; e = e->next)
    if (e->alignment)
      a = &e->next;
    else
      {
	*a = e->next;
	if (e->len)
	  {
	    e->secinfo = e->u.suffix->secinfo;
	    e->alignment = e->u.suffix->alignment;
	    e->u.index = e->u.suffix->u.index + (e->u.suffix->len - e->len);
	  }
      }
}