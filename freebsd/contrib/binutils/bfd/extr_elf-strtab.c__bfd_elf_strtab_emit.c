#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct elf_strtab_hash {size_t size; size_t sec_size; TYPE_2__** array; } ;
typedef  size_t bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {char* string; } ;
struct TYPE_4__ {scalar_t__ refcount; unsigned int len; TYPE_1__ root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int bfd_bwrite (char const*,unsigned int,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_strtab_emit (register bfd *abfd, struct elf_strtab_hash *tab)
{
  bfd_size_type off = 1, i;

  if (bfd_bwrite ("", 1, abfd) != 1)
    return FALSE;

  for (i = 1; i < tab->size; ++i)
    {
      register const char *str;
      register unsigned int len;

      BFD_ASSERT (tab->array[i]->refcount == 0);
      len = tab->array[i]->len;
      if ((int) len < 0)
	continue;

      str = tab->array[i]->root.string;
      if (bfd_bwrite (str, len, abfd) != len)
	return FALSE;

      off += len;
    }

  BFD_ASSERT (off == tab->sec_size);
  return TRUE;
}