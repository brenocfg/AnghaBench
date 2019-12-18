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

/* Variables and functions */
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  free_split_directories (char**) ; 
 scalar_t__ malloc (int) ; 
 char* save_string (char const*,int) ; 

__attribute__((used)) static char **
split_directories (const char *name, int *ptr_num_dirs)
{
  int num_dirs = 0;
  char **dirs;
  const char *p, *q;
  int ch;

  /* Count the number of directories.  Special case MSDOS disk names as part
     of the initial directory.  */
  p = name;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  if (name[1] == ':' && IS_DIR_SEPARATOR (name[2]))
    {
      p += 3;
      num_dirs++;
    }
#endif /* HAVE_DOS_BASED_FILE_SYSTEM */

  while ((ch = *p++) != '\0')
    {
      if (IS_DIR_SEPARATOR (ch))
	{
	  num_dirs++;
	  while (IS_DIR_SEPARATOR (*p))
	    p++;
	}
    }

  dirs = (char **) malloc (sizeof (char *) * (num_dirs + 2));
  if (dirs == NULL)
    return NULL;

  /* Now copy the directory parts.  */
  num_dirs = 0;
  p = name;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  if (name[1] == ':' && IS_DIR_SEPARATOR (name[2]))
    {
      dirs[num_dirs++] = save_string (p, 3);
      if (dirs[num_dirs - 1] == NULL)
	{
	  free (dirs);
	  return NULL;
	}
      p += 3;
    }
#endif /* HAVE_DOS_BASED_FILE_SYSTEM */

  q = p;
  while ((ch = *p++) != '\0')
    {
      if (IS_DIR_SEPARATOR (ch))
	{
	  while (IS_DIR_SEPARATOR (*p))
	    p++;

	  dirs[num_dirs++] = save_string (q, p - q);
	  if (dirs[num_dirs - 1] == NULL)
	    {
	      dirs[num_dirs] = NULL;
	      free_split_directories (dirs);
	      return NULL;
	    }
	  q = p;
	}
    }

  if (p - 1 - q > 0)
    dirs[num_dirs++] = save_string (q, p - 1 - q);
  dirs[num_dirs] = NULL;

  if (dirs[num_dirs - 1] == NULL)
    {
      free_split_directories (dirs);
      return NULL;
    }

  if (ptr_num_dirs)
    *ptr_num_dirs = num_dirs;
  return dirs;
}