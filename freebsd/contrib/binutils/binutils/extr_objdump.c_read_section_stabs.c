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
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 char* FALSE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int exit_status ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  non_fatal (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
read_section_stabs (bfd *abfd, const char *sect_name, bfd_size_type *size_ptr)
{
  asection *stabsect;
  bfd_size_type size;
  char *contents;

  stabsect = bfd_get_section_by_name (abfd, sect_name);
  if (stabsect == NULL)
    {
      printf (_("No %s section present\n\n"), sect_name);
      return FALSE;
    }

  size = bfd_section_size (abfd, stabsect);
  contents  = xmalloc (size);

  if (! bfd_get_section_contents (abfd, stabsect, contents, 0, size))
    {
      non_fatal (_("Reading %s section of %s failed: %s"),
		 sect_name, bfd_get_filename (abfd),
		 bfd_errmsg (bfd_get_error ()));
      free (contents);
      exit_status = 1;
      return NULL;
    }

  *size_ptr = size;

  return contents;
}