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
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  unsigned long bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (unsigned long*) ; 
 int /*<<< orphan*/  GNU_DEBUGLINK ; 
 unsigned long bfd_get_32 (unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
get_debug_link_info (bfd *abfd, unsigned long *crc32_out)
{
  asection *sect;
  unsigned long crc32;
  bfd_byte *contents;
  int crc_offset;
  char *name;

  BFD_ASSERT (abfd);
  BFD_ASSERT (crc32_out);

  sect = bfd_get_section_by_name (abfd, GNU_DEBUGLINK);

  if (sect == NULL)
    return NULL;

  if (!bfd_malloc_and_get_section (abfd, sect, &contents))
    {
      if (contents != NULL)
	free (contents);
      return NULL;
    }

  /* Crc value is stored after the filename, aligned up to 4 bytes.  */
  name = (char *) contents;
  crc_offset = strlen (name) + 1;
  crc_offset = (crc_offset + 3) & ~3;

  crc32 = bfd_get_32 (abfd, contents + crc_offset);

  *crc32_out = crc32;
  return name;
}