#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct objalloc {int dummy; } ;
struct TYPE_4__ {scalar_t__ memory; int /*<<< orphan*/  section_htab; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_hash_table_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  objalloc_free (struct objalloc*) ; 

void
_bfd_delete_bfd (bfd *abfd)
{
  if (abfd->memory)
    {
      bfd_hash_table_free (&abfd->section_htab);
      objalloc_free ((struct objalloc *) abfd->memory);
    }
  free (abfd);
}