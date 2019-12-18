#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct objfile {int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/ * obfd; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {int /*<<< orphan*/  filepos; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ bfd_bread (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_size (TYPE_1__*) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ symfile_relocate_debug_section (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

char *
dwarf2_read_section (struct objfile *objfile, asection *sectp)
{
  bfd *abfd = objfile->obfd;
  char *buf, *retbuf;
  bfd_size_type size = bfd_get_section_size (sectp);

  if (size == 0)
    return NULL;

  buf = (char *) obstack_alloc (&objfile->objfile_obstack, size);
  retbuf
    = (char *) symfile_relocate_debug_section (abfd, sectp, (bfd_byte *) buf);
  if (retbuf != NULL)
    return retbuf;

  if (bfd_seek (abfd, sectp->filepos, SEEK_SET) != 0
      || bfd_bread (buf, size, abfd) != size)
    error ("Dwarf Error: Can't read DWARF data from '%s'",
	   bfd_get_filename (abfd));

  return buf;
}