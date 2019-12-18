#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_13__ {struct TYPE_13__* archive_next; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  PROGRESS (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_check_format_matches (TYPE_1__*,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (TYPE_1__*) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_error_no_error ; 
 scalar_t__ bfd_error_no_more_archived_files ; 
 int /*<<< orphan*/  bfd_fatal (char const*) ; 
 scalar_t__ bfd_get_error () ; 
 char* bfd_get_target (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_nonfatal (char const*) ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_1__* bfd_openr (char const*,char const*) ; 
 TYPE_1__* bfd_openr_next_archived_file (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* bfd_openw (char const*,char const*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int /*<<< orphan*/  maybequit () ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  operation_alters_arch ; 
 char const* output_filename ; 
 int /*<<< orphan*/  perror (char const*) ; 
 char* program_name ; 
 int /*<<< orphan*/  silent_create ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xexit (int) ; 

bfd *
open_inarch (const char *archive_filename, const char *file)
{
  const char *target;
  bfd **last_one;
  bfd *next_one;
  struct stat sbuf;
  bfd *arch;
  char **matching;

  bfd_set_error (bfd_error_no_error);

  target = NULL;

  if (stat (archive_filename, &sbuf) != 0)
    {
#if !defined(__GO32__) || defined(__DJGPP__)

      /* FIXME: I don't understand why this fragment was ifndef'ed
	 away for __GO32__; perhaps it was in the days of DJGPP v1.x.
	 stat() works just fine in v2.x, so I think this should be
	 removed.  For now, I enable it for DJGPP v2. -- EZ.  */

/* KLUDGE ALERT! Temporary fix until I figger why
   stat() is wrong ... think it's buried in GO32's IDT - Jax */
      if (errno != ENOENT)
	bfd_fatal (archive_filename);
#endif

      if (!operation_alters_arch)
	{
	  fprintf (stderr, "%s: ", program_name);
	  perror (archive_filename);
	  maybequit ();
	  return NULL;
	}

      /* Try to figure out the target to use for the archive from the
         first object on the list.  */
      if (file != NULL)
	{
	  bfd *obj;

	  obj = bfd_openr (file, NULL);
	  if (obj != NULL)
	    {
	      if (bfd_check_format (obj, bfd_object))
		target = bfd_get_target (obj);
	      (void) bfd_close (obj);
	    }
	}

      /* Create an empty archive.  */
      arch = bfd_openw (archive_filename, target);
      if (arch == NULL
	  || ! bfd_set_format (arch, bfd_archive)
	  || ! bfd_close (arch))
	bfd_fatal (archive_filename);
      else if (!silent_create)
        non_fatal (_("creating %s"), archive_filename);

      /* If we die creating a new archive, don't leave it around.  */
      output_filename = archive_filename;
    }

  arch = bfd_openr (archive_filename, target);
  if (arch == NULL)
    {
    bloser:
      bfd_fatal (archive_filename);
    }

  if (! bfd_check_format_matches (arch, bfd_archive, &matching))
    {
      bfd_nonfatal (archive_filename);
      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (matching);
	  free (matching);
	}
      xexit (1);
    }

  last_one = &(arch->archive_next);
  /* Read all the contents right away, regardless.  */
  for (next_one = bfd_openr_next_archived_file (arch, NULL);
       next_one;
       next_one = bfd_openr_next_archived_file (arch, next_one))
    {
      PROGRESS (1);
      *last_one = next_one;
      last_one = &next_one->archive_next;
    }
  *last_one = (bfd *) NULL;
  if (bfd_get_error () != bfd_error_no_more_archived_files)
    goto bloser;
  return arch;
}