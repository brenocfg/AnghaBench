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
struct file_data {int desc; int /*<<< orphan*/  name; } ;
struct dirent {char* d_name; } ;
struct dirdata {char const** names; char* data; size_t nnames; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int NAMLEN (struct dirent*) ; 
 int PTRDIFF_MAX ; 
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  excluded ; 
 scalar_t__ excluded_filename (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xalloc_die () ; 
 void* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static bool
dir_read (struct file_data const *dir, struct dirdata *dirdata)
{
  register struct dirent *next;
  register size_t i;

  /* Address of block containing the files that are described.  */
  char const **names;

  /* Number of files in directory.  */
  size_t nnames;

  /* Allocated and used storage for file name data.  */
  char *data;
  size_t data_alloc, data_used;

  dirdata->names = 0;
  dirdata->data = 0;
  nnames = 0;
  data = 0;

  if (dir->desc != -1)
    {
      /* Open the directory and check for errors.  */
      register DIR *reading = opendir (dir->name);
      if (!reading)
	return false;

      /* Initialize the table of filenames.  */

      data_alloc = 512;
      data_used = 0;
      dirdata->data = data = xmalloc (data_alloc);

      /* Read the directory entries, and insert the subfiles
	 into the `data' table.  */

      while ((errno = 0, (next = readdir (reading)) != 0))
	{
	  char *d_name = next->d_name;
	  size_t d_size = NAMLEN (next) + 1;

	  /* Ignore "." and "..".  */
	  if (d_name[0] == '.'
	      && (d_name[1] == 0 || (d_name[1] == '.' && d_name[2] == 0)))
	    continue;

	  if (excluded_filename (excluded, d_name))
	    continue;

	  while (data_alloc < data_used + d_size)
	    {
	      if (PTRDIFF_MAX / 2 <= data_alloc)
		xalloc_die ();
	      dirdata->data = data = xrealloc (data, data_alloc *= 2);
	    }

	  memcpy (data + data_used, d_name, d_size);
	  data_used += d_size;
	  nnames++;
	}
      if (errno)
	{
	  int e = errno;
	  closedir (reading);
	  errno = e;
	  return false;
	}
#if CLOSEDIR_VOID
      closedir (reading);
#else
      if (closedir (reading) != 0)
	return false;
#endif
    }

  /* Create the `names' table from the `data' table.  */
  if (PTRDIFF_MAX / sizeof *names - 1 <= nnames)
    xalloc_die ();
  dirdata->names = names = xmalloc ((nnames + 1) * sizeof *names);
  dirdata->nnames = nnames;
  for (i = 0;  i < nnames;  i++)
    {
      names[i] = data;
      data += strlen (data) + 1;
    }
  names[nnames] = 0;
  return true;
}