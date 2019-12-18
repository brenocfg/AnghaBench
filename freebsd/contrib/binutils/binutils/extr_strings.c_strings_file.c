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
typedef  int /*<<< orphan*/  statbuf ;
typedef  int /*<<< orphan*/  file_off ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FOPEN_RB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  datasection_only ; 
 scalar_t__ errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * file_open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_stat (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_strings (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strings_object_file (char*) ; 

__attribute__((used)) static bfd_boolean
strings_file (char *file)
{
  statbuf st;

  if (file_stat (file, &st) < 0)
    {
      if (errno == ENOENT)
	non_fatal (_("'%s': No such file"), file);
      else
	non_fatal (_("Warning: could not locate '%s'.  reason: %s"),
		   file, strerror (errno));
      return FALSE;
    }

  /* If we weren't told to scan the whole file,
     try to open it as an object file and only look at
     initialized data sections.  If that fails, fall back to the
     whole file.  */
  if (!datasection_only || !strings_object_file (file))
    {
      FILE *stream;

      stream = file_open (file, FOPEN_RB);
      if (stream == NULL)
	{
	  fprintf (stderr, "%s: ", program_name);
	  perror (file);
	  return FALSE;
	}

      print_strings (file, stream, (file_off) 0, 0, 0, (char *) 0);

      if (fclose (stream) == EOF)
	{
	  fprintf (stderr, "%s: ", program_name);
	  perror (file);
	  return FALSE;
	}
    }

  return TRUE;
}