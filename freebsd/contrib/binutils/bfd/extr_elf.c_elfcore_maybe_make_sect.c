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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/  alignment_power; int /*<<< orphan*/  filepos; int /*<<< orphan*/  size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elfcore_maybe_make_sect (bfd *abfd, char *name, asection *sect)
{
  asection *sect2;

  if (bfd_get_section_by_name (abfd, name) != NULL)
    return TRUE;

  sect2 = bfd_make_section_with_flags (abfd, name, sect->flags);
  if (sect2 == NULL)
    return FALSE;

  sect2->size = sect->size;
  sect2->filepos = sect->filepos;
  sect2->alignment_power = sect->alignment_power;
  return TRUE;
}