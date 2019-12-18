#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct elf_obj_tdata {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {int /*<<< orphan*/ * any; } ;
struct TYPE_8__ {TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_9__ {scalar_t__ program_header_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_zalloc (TYPE_2__*,int) ; 
 TYPE_3__* elf_tdata (TYPE_2__*) ; 

bfd_boolean
bfd_elf_mkobject (bfd *abfd)
{
  if (abfd->tdata.any == NULL)
    {
      abfd->tdata.any = bfd_zalloc (abfd, sizeof (struct elf_obj_tdata));
      if (abfd->tdata.any == NULL)
	return FALSE;
    }

  elf_tdata (abfd)->program_header_size = (bfd_size_type) -1;

  return TRUE;
}