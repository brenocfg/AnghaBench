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
struct TYPE_2__ {void* index; struct elf_strtab_hash_entry* suffix; } ;
struct elf_strtab_hash_entry {int len; TYPE_1__ u; scalar_t__ refcount; } ;
struct elf_strtab_hash {int size; struct elf_strtab_hash_entry** array; void* sec_size; } ;
typedef  void* bfd_size_type ;

/* Variables and functions */
 struct elf_strtab_hash_entry** bfd_malloc (void*) ; 
 int /*<<< orphan*/  free (struct elf_strtab_hash_entry**) ; 
 scalar_t__ is_suffix (struct elf_strtab_hash_entry*,struct elf_strtab_hash_entry*) ; 
 int /*<<< orphan*/  qsort (struct elf_strtab_hash_entry**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strrevcmp ; 

void
_bfd_elf_strtab_finalize (struct elf_strtab_hash *tab)
{
  struct elf_strtab_hash_entry **array, **a, *e;
  bfd_size_type size, amt;

  /* GCC 2.91.66 (egcs-1.1.2) on i386 miscompiles this function when i is
     a 64-bit bfd_size_type: a 64-bit target or --enable-64-bit-bfd.
     Besides, indexing with a long long wouldn't give anything but extra
     cycles.  */
  size_t i;

  /* Sort the strings by suffix and length.  */
  amt = tab->size * sizeof (struct elf_strtab_hash_entry *);
  array = bfd_malloc (amt);
  if (array == NULL)
    goto alloc_failure;

  for (i = 1, a = array; i < tab->size; ++i)
    {
      e = tab->array[i];
      if (e->refcount)
	{
	  *a++ = e;
	  /* Adjust the length to not include the zero terminator.  */
	  e->len -= 1;
	}
      else
	e->len = 0;
    }

  size = a - array;
  if (size != 0)
    {
      qsort (array, size, sizeof (struct elf_strtab_hash_entry *), strrevcmp);

      /* Loop over the sorted array and merge suffixes.  Start from the
	 end because we want eg.

	 s1 -> "d"
	 s2 -> "bcd"
	 s3 -> "abcd"

	 to end up as

	 s3 -> "abcd"
	 s2 _____^
	 s1 _______^

	 ie. we don't want s1 pointing into the old s2.  */
      e = *--a;
      e->len += 1;
      while (--a >= array)
	{
	  struct elf_strtab_hash_entry *cmp = *a;

	  cmp->len += 1;
	  if (is_suffix (e, cmp))
	    {
	      cmp->u.suffix = e;
	      cmp->len = -cmp->len;
	    }
	  else
	    e = cmp;
	}
    }

alloc_failure:
  if (array)
    free (array);

  /* Assign positions to the strings we want to keep.  */
  size = 1;
  for (i = 1; i < tab->size; ++i)
    {
      e = tab->array[i];
      if (e->refcount && e->len > 0)
	{
	  e->u.index = size;
	  size += e->len;
	}
    }

  tab->sec_size = size;

  /* Adjust the rest.  */
  for (i = 1; i < tab->size; ++i)
    {
      e = tab->array[i];
      if (e->refcount && e->len < 0)
	e->u.index = e->u.suffix->u.index + (e->u.suffix->len + e->len);
    }
}