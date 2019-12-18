#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sec_ptr ;
typedef  scalar_t__ file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {scalar_t__ filepos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_bwrite (void const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_generic_set_section_contents (bfd *abfd,
				   sec_ptr section,
				   const void *location,
				   file_ptr offset,
				   bfd_size_type count)
{
  if (count == 0)
    return TRUE;

  if (bfd_seek (abfd, section->filepos + offset, SEEK_SET) != 0
      || bfd_bwrite (location, count, abfd) != count)
    return FALSE;

  return TRUE;
}