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
typedef  int symindex ;
struct TYPE_3__ {int /*<<< orphan*/  file_offset; } ;
typedef  TYPE_1__ carsym ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {TYPE_1__* symdefs; } ;

/* Variables and functions */
 int /*<<< orphan*/ * _bfd_get_elt_at_filepos (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* bfd_ardata (int /*<<< orphan*/ *) ; 

bfd *
_bfd_generic_get_elt_at_index (bfd *abfd, symindex index)
{
  carsym *entry;

  entry = bfd_ardata (abfd)->symdefs + index;
  return _bfd_get_elt_at_filepos (abfd, entry->file_offset);
}