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
struct bfd_strtab_hash {int /*<<< orphan*/  xcoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 struct bfd_strtab_hash* _bfd_stringtab_init () ; 

struct bfd_strtab_hash *
_bfd_xcoff_stringtab_init (void)
{
  struct bfd_strtab_hash *ret;

  ret = _bfd_stringtab_init ();
  if (ret != NULL)
    ret->xcoff = TRUE;
  return ret;
}