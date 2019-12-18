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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_fatal (char const*) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  bfd_nonfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,char const*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  free (char**) ; 
 int get_file_size (char const*) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int /*<<< orphan*/  slurp_symtab (int /*<<< orphan*/ *) ; 
 char** syms ; 
 int /*<<< orphan*/  translate_addresses (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xexit (int) ; 

__attribute__((used)) static int
process_file (const char *file_name, const char *section_name,
	      const char *target)
{
  bfd *abfd;
  asection *section;
  char **matching;

  if (get_file_size (file_name) < 1)
    return 1;

  abfd = bfd_openr (file_name, target);
  if (abfd == NULL)
    bfd_fatal (file_name);

  if (bfd_check_format (abfd, bfd_archive))
    fatal (_("%s: cannot get addresses from archive"), file_name);

  if (! bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      bfd_nonfatal (bfd_get_filename (abfd));
      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (matching);
	  free (matching);
	}
      xexit (1);
    }

  if (section_name != NULL)
    {
      section = bfd_get_section_by_name (abfd, section_name);
      if (section == NULL)
	fatal (_("%s: cannot find section %s"), file_name, section_name);
    }
  else
    section = NULL;

  slurp_symtab (abfd);

  translate_addresses (abfd, section);

  if (syms != NULL)
    {
      free (syms);
      syms = NULL;
    }

  bfd_close (abfd);

  return 0;
}