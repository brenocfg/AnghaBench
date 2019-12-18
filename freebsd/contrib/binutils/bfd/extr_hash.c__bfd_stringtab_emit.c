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
struct TYPE_2__ {char* string; } ;
struct strtab_hash_entry {TYPE_1__ root; struct strtab_hash_entry* next; } ;
struct bfd_strtab_hash {struct strtab_hash_entry* first; scalar_t__ xcoff; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 size_t bfd_bwrite (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

bfd_boolean
_bfd_stringtab_emit (bfd *abfd, struct bfd_strtab_hash *tab)
{
  bfd_boolean xcoff;
  struct strtab_hash_entry *entry;

  xcoff = tab->xcoff;

  for (entry = tab->first; entry != NULL; entry = entry->next)
    {
      const char *str;
      size_t len;

      str = entry->root.string;
      len = strlen (str) + 1;

      if (xcoff)
	{
	  bfd_byte buf[2];

	  /* The output length includes the null byte.  */
	  bfd_put_16 (abfd, (bfd_vma) len, buf);
	  if (bfd_bwrite ((void *) buf, (bfd_size_type) 2, abfd) != 2)
	    return FALSE;
	}

      if (bfd_bwrite ((void *) str, (bfd_size_type) len, abfd) != len)
	return FALSE;
    }

  return TRUE;
}