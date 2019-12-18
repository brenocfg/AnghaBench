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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_openr_next_archived_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mcore_elf_cache_filename (char*) ; 
 scalar_t__ mcore_elf_out_file ; 
 int /*<<< orphan*/  scan_open_obj_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scan_obj_file (const char *filename)
{
  bfd * f = bfd_openr (filename, 0);

  if (!f)
    /* xgettext:c-format */
    fatal (_("Unable to open object file: %s"), filename);

  /* xgettext:c-format */
  inform (_("Scanning object file %s"), filename);

  if (bfd_check_format (f, bfd_archive))
    {
      bfd *arfile = bfd_openr_next_archived_file (f, 0);
      while (arfile)
	{
	  if (bfd_check_format (arfile, bfd_object))
	    scan_open_obj_file (arfile);
	  bfd_close (arfile);
	  arfile = bfd_openr_next_archived_file (f, arfile);
	}

#ifdef DLLTOOL_MCORE_ELF
      if (mcore_elf_out_file)
	inform (_("Cannot produce mcore-elf dll from archive file: %s"), filename);
#endif
    }
  else if (bfd_check_format (f, bfd_object))
    {
      scan_open_obj_file (f);

#ifdef DLLTOOL_MCORE_ELF
      if (mcore_elf_out_file)
	mcore_elf_cache_filename ((char *) filename);
#endif
    }

  bfd_close (f);
}