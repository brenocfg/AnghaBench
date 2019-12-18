#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ debug_information_part; } ;
struct TYPE_9__ {TYPE_1__ r; } ;
struct TYPE_10__ {TYPE_2__ w; } ;
typedef  TYPE_3__ ieee_data_type ;
typedef  int flagword ;
typedef  scalar_t__ file_ptr ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_11__ {scalar_t__ filepos; scalar_t__ size; } ;
typedef  TYPE_4__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* IEEE_DATA (int /*<<< orphan*/ *) ; 
 int SEC_DEBUGGING ; 
 int SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* bfd_make_section_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ ieee_part_after (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
ieee_slurp_debug (bfd *abfd)
{
  ieee_data_type *ieee = IEEE_DATA (abfd);
  asection *sec;
  file_ptr debug_end;
  flagword flags;

  if (ieee->w.r.debug_information_part == 0)
    return TRUE;

  flags = SEC_DEBUGGING | SEC_HAS_CONTENTS;
  sec = bfd_make_section_with_flags (abfd, ".debug", flags);
  if (sec == NULL)
    return FALSE;
  sec->filepos = ieee->w.r.debug_information_part;

  debug_end = ieee_part_after (ieee, ieee->w.r.debug_information_part);
  sec->size = debug_end - ieee->w.r.debug_information_part;

  return TRUE;
}