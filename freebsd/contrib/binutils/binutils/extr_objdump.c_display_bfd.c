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
 scalar_t__ bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_core ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 scalar_t__ bfd_error_file_not_recognized ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  dump_bfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int /*<<< orphan*/  nonfatal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
display_bfd (bfd *abfd)
{
  char **matching;

  if (bfd_check_format_matches (abfd, bfd_object, &matching))
    {
      dump_bfd (abfd);
      return;
    }

  if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
    {
      nonfatal (bfd_get_filename (abfd));
      list_matching_formats (matching);
      free (matching);
      return;
    }

  if (bfd_get_error () != bfd_error_file_not_recognized)
    {
      nonfatal (bfd_get_filename (abfd));
      return;
    }

  if (bfd_check_format_matches (abfd, bfd_core, &matching))
    {
      dump_bfd (abfd);
      return;
    }

  nonfatal (bfd_get_filename (abfd));

  if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
    {
      list_matching_formats (matching);
      free (matching);
    }
}