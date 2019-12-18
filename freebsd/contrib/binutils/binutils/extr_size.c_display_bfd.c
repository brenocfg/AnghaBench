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

/* Variables and functions */
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_core ; 
 char* bfd_core_file_failing_command (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int /*<<< orphan*/  print_sizes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int return_code ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
display_bfd (bfd *abfd)
{
  char **matching;

  if (bfd_check_format (abfd, bfd_archive))
    /* An archive within an archive.  */
    return;

  if (bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      print_sizes (abfd);
      printf ("\n");
      return;
    }

  if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
    {
      bfd_nonfatal (bfd_get_filename (abfd));
      list_matching_formats (matching);
      free (matching);
      return_code = 3;
      return;
    }

  if (bfd_check_format_matches (abfd, bfd_core, &matching))
    {
      const char *core_cmd;

      print_sizes (abfd);
      fputs (" (core file", stdout);

      core_cmd = bfd_core_file_failing_command (abfd);
      if (core_cmd)
	printf (" invoked as %s", core_cmd);

      puts (")\n");
      return;
    }

  bfd_nonfatal (bfd_get_filename (abfd));

  if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
    {
      list_matching_formats (matching);
      free (matching);
    }

  return_code = 3;
}