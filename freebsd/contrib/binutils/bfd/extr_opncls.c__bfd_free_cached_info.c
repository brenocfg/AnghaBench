#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct objalloc {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {int /*<<< orphan*/ * any; } ;
struct TYPE_5__ {int /*<<< orphan*/ * memory; int /*<<< orphan*/ * usrdata; TYPE_1__ tdata; int /*<<< orphan*/ * outsymbols; int /*<<< orphan*/ * section_last; int /*<<< orphan*/ * sections; int /*<<< orphan*/  section_htab; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objalloc_free (struct objalloc*) ; 

bfd_boolean
_bfd_free_cached_info (bfd *abfd)
{
  if (abfd->memory)
    {
      bfd_hash_table_free (&abfd->section_htab);
      objalloc_free ((struct objalloc *) abfd->memory);

      abfd->sections = NULL;
      abfd->section_last = NULL;
      abfd->outsymbols = NULL;
      abfd->tdata.any = NULL;
      abfd->usrdata = NULL;
      abfd->memory = NULL;
    }

  return TRUE;
}