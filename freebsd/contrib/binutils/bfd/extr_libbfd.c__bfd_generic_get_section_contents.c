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
struct TYPE_3__ {scalar_t__ rawsize; scalar_t__ size; scalar_t__ filepos; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_bread (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_generic_get_section_contents (bfd *abfd,
				   sec_ptr section,
				   void *location,
				   file_ptr offset,
				   bfd_size_type count)
{
  bfd_size_type sz;
  if (count == 0)
    return TRUE;

  sz = section->rawsize ? section->rawsize : section->size;
  if (offset + count > sz)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  if (bfd_seek (abfd, section->filepos + offset, SEEK_SET) != 0
      || bfd_bread (location, count, abfd) != count)
    return FALSE;

  return TRUE;
}