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
 int O_BINARY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_archive ; 
 int /*<<< orphan*/  bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_fatal (char const*) ; 
 int /*<<< orphan*/ * bfd_fdopenr (char const*,char const*,int) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_has_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (char const*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_update_armap_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int get_file_size (char const*) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ranlib_only (char const*) ; 
 int /*<<< orphan*/  xexit (int) ; 

__attribute__((used)) static int
ranlib_touch (const char *archname)
{
#ifdef __GO32__
  /* I don't think updating works on go32.  */
  ranlib_only (archname);
#else
  int f;
  bfd *arch;
  char **matching;

  if (get_file_size (archname) < 1)
    return 1;
  f = open (archname, O_RDWR | O_BINARY, 0);
  if (f < 0)
    {
      bfd_set_error (bfd_error_system_call);
      bfd_fatal (archname);
    }

  arch = bfd_fdopenr (archname, (const char *) NULL, f);
  if (arch == NULL)
    bfd_fatal (archname);
  if (! bfd_check_format_matches (arch, bfd_archive, &matching))
    {
      bfd_nonfatal (archname);
      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (matching);
	  free (matching);
	}
      xexit (1);
    }

  if (! bfd_has_map (arch))
    /* xgettext:c-format */
    fatal (_("%s: no archive map to update"), archname);

  bfd_update_armap_timestamp (arch);

  if (! bfd_close (arch))
    bfd_fatal (archname);
#endif
  return 0;
}