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
typedef  int /*<<< orphan*/  file_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 char* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ bfd_bread (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_no_debug_section ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
build_debug_section (bfd *abfd)
{
  char *debug_section;
  file_ptr position;
  bfd_size_type sec_size;

  asection *sect = bfd_get_section_by_name (abfd, ".debug");

  if (!sect)
    {
      bfd_set_error (bfd_error_no_debug_section);
      return NULL;
    }

  sec_size = sect->size;
  debug_section = bfd_alloc (abfd, sec_size);
  if (debug_section == NULL)
    return NULL;

  /* Seek to the beginning of the `.debug' section and read it.
     Save the current position first; it is needed by our caller.
     Then read debug section and reset the file pointer.  */

  position = bfd_tell (abfd);
  if (bfd_seek (abfd, sect->filepos, SEEK_SET) != 0
      || bfd_bread (debug_section, sec_size, abfd) != sec_size
      || bfd_seek (abfd, position, SEEK_SET) != 0)
    return NULL;
  return debug_section;
}