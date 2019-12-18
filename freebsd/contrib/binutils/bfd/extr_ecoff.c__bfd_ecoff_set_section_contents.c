#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ file_ptr ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {int /*<<< orphan*/  output_has_begun; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_10__ {scalar_t__ filepos; int /*<<< orphan*/  lma; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _LIB ; 
 int bfd_bwrite (void const*,int,TYPE_1__*) ; 
 int bfd_get_32 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecoff_compute_section_file_positions (TYPE_1__*) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_ecoff_set_section_contents (bfd *abfd,
				 asection *section,
				 const void * location,
				 file_ptr offset,
				 bfd_size_type count)
{
  file_ptr pos;

  /* This must be done first, because bfd_set_section_contents is
     going to set output_has_begun to TRUE.  */
  if (! abfd->output_has_begun
      && ! ecoff_compute_section_file_positions (abfd))
    return FALSE;

  /* Handle the .lib section specially so that Irix 4 shared libraries
     work out.  See coff_set_section_contents in coffcode.h.  */
  if (streq (section->name, _LIB))
    {
      bfd_byte *rec, *recend;

      rec = (bfd_byte *) location;
      recend = rec + count;
      while (rec < recend)
	{
	  ++section->lma;
	  rec += bfd_get_32 (abfd, rec) * 4;
	}

      BFD_ASSERT (rec == recend);
    }

  if (count == 0)
    return TRUE;

  pos = section->filepos + offset;
  if (bfd_seek (abfd, pos, SEEK_SET) != 0
      || bfd_bwrite (location, count, abfd) != count)
    return FALSE;

  return TRUE;
}