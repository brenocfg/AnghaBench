#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 unsigned long MAX_NOTESZ ; 
 unsigned long bfd_h_get_32 (int /*<<< orphan*/ *,char const*) ; 
 unsigned long bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 unsigned long strlen (char const*) ; 

__attribute__((used)) static int
check_note (bfd *abfd, asection *sect, const char *note,
	    const char *name, unsigned long descsz, unsigned long type)
{
  unsigned long notesz;
  unsigned long rdescsz;

  /* Calculate the size of this note.  */
  notesz = 4 * 3;	/* namelen, optlen, type */
  notesz += strlen (name) + 1;
  notesz = ((notesz + 3) & ~3);

  /* If this assertion triggers, increase MAX_NOTESZ.  */
  gdb_assert (notesz <= MAX_NOTESZ);

  /* Check whether SECT is big enough to comtain the complete note.  */
  if (notesz > bfd_section_size (abfd, sect))
    return 0;

  /* Check the note name.  */
  if (bfd_h_get_32 (abfd, note) != (strlen (name) + 1)
      || strcmp (note + 12, name) != 0)
    return 0;

  /* Check the descriptor size.  */
  rdescsz = bfd_h_get_32 (abfd, note + 4);
  if (descsz != (unsigned long)-1 && rdescsz != descsz)
    return 0;

  notesz += rdescsz;
  notesz = ((notesz + 3) & ~3);

  /* Check whether SECT is big enough to comtain the complete note.  */
  if (notesz > bfd_section_size (abfd, sect))
    return 0;

  /* Check the note type.  */
  if (bfd_h_get_32 (abfd, note + 8) != type)
    return 0;

  return 1;
}