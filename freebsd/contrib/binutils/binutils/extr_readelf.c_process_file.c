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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARMAG ; 
 scalar_t__ ENOENT ; 
 int SARMAG ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ archive_file_offset ; 
 scalar_t__ archive_file_size ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int process_archive (char*,int /*<<< orphan*/ *) ; 
 int process_object (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static int
process_file (char *file_name)
{
  FILE *file;
  struct stat statbuf;
  char armag[SARMAG];
  int ret;

  if (stat (file_name, &statbuf) < 0)
    {
      if (errno == ENOENT)
	error (_("'%s': No such file\n"), file_name);
      else
	error (_("Could not locate '%s'.  System error message: %s\n"),
	       file_name, strerror (errno));
      return 1;
    }

  if (! S_ISREG (statbuf.st_mode))
    {
      error (_("'%s' is not an ordinary file\n"), file_name);
      return 1;
    }

  file = fopen (file_name, "rb");
  if (file == NULL)
    {
      error (_("Input file '%s' is not readable.\n"), file_name);
      return 1;
    }

  if (fread (armag, SARMAG, 1, file) != 1)
    {
      error (_("%s: Failed to read file header\n"), file_name);
      fclose (file);
      return 1;
    }

  if (memcmp (armag, ARMAG, SARMAG) == 0)
    ret = process_archive (file_name, file);
  else
    {
      rewind (file);
      archive_file_size = archive_file_offset = 0;
      ret = process_object (file_name, file);
    }

  fclose (file);

  return ret;
}