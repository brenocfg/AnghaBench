#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfd_strtab_hash {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _bfd_stringtab_add (struct bfd_strtab_hash*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_stringtab_free (struct bfd_strtab_hash*) ; 
 struct bfd_strtab_hash* _bfd_stringtab_init () ; 

struct bfd_strtab_hash *
_bfd_elf_stringtab_init (void)
{
  struct bfd_strtab_hash *ret;

  ret = _bfd_stringtab_init ();
  if (ret != NULL)
    {
      bfd_size_type loc;

      loc = _bfd_stringtab_add (ret, "", TRUE, FALSE);
      BFD_ASSERT (loc == 0 || loc == (bfd_size_type) -1);
      if (loc == (bfd_size_type) -1)
	{
	  _bfd_stringtab_free (ret);
	  ret = NULL;
	}
    }
  return ret;
}