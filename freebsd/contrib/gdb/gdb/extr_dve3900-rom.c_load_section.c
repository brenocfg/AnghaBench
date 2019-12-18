#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  header ;
typedef  scalar_t__ bfd_vma ;
typedef  unsigned int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int SEC_LOAD ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ bfd_section_lma (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ *,TYPE_1__*) ; 
 unsigned int bfd_section_size (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  print_address_numeric (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  process_read_request (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  write_long (unsigned char*,long) ; 
 int /*<<< orphan*/  xfree (unsigned char*) ; 
 scalar_t__ xmalloc (unsigned int) ; 

__attribute__((used)) static void
load_section (bfd *abfd, asection *s, unsigned int *data_count)
{
  if (s->flags & SEC_LOAD)
    {
      bfd_size_type section_size = bfd_section_size (abfd, s);
      bfd_vma section_base = bfd_section_lma (abfd, s);
      unsigned char *buffer;
      unsigned char header[8];

      /* Don't output zero-length sections.  */
      if (section_size == 0)
	return;
      if (data_count)
	*data_count += section_size;

      /* Print some fluff about the section being loaded.  */
      printf_filtered ("Loading section %s, size 0x%lx lma ",
		       bfd_section_name (abfd, s), (long) section_size);
      print_address_numeric (section_base, 1, gdb_stdout);
      printf_filtered ("\n");
      gdb_flush (gdb_stdout);

      /* Write the section header (location and size).  */
      write_long (&header[0], (long) section_base);
      write_long (&header[4], (long) section_size);
      process_read_request (header, sizeof (header));

      /* Read the section contents into a buffer, write it out,
         then free the buffer.  */
      buffer = (unsigned char *) xmalloc (section_size);
      bfd_get_section_contents (abfd, s, buffer, 0, section_size);
      process_read_request (buffer, section_size);
      xfree (buffer);
    }
}