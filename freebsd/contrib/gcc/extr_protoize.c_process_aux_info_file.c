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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_mtime; size_t st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_SEPARATOR ; 
 int /*<<< orphan*/  DIR_SEPARATOR_2 ; 
 int ENOENT ; 
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char*) ; 
 scalar_t__ IS_DIR_SEPARATOR (char) ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  R_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 char* alloca (size_t) ; 
 char const* aux_info_file_name ; 
 char const* aux_info_suffix ; 
 char const* base_source_file_name ; 
 scalar_t__ close (int) ; 
 int current_aux_info_lineno ; 
 int errno ; 
 int /*<<< orphan*/  errors ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gen_aux_info_file (char const*) ; 
 char* invocation_filename ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,char*,...) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  pname ; 
 scalar_t__ referenced_file_is_newer (char const*,scalar_t__) ; 
 int safe_read (int,char*,size_t) ; 
 int /*<<< orphan*/  save_def_or_dec (char const*,int) ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,char const*) ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* strrchr (char*,int /*<<< orphan*/ ) ; 
 char* unexpand_if_needed (char const*) ; 
 int unlink (char*) ; 
 char* xmalloc (size_t) ; 
 int /*<<< orphan*/  xstrerror (int) ; 

__attribute__((used)) static void
process_aux_info_file (const char *base_source_filename, int keep_it,
		       int is_syscalls)
{
  size_t base_len = strlen (base_source_filename);
  char * aux_info_filename = alloca (base_len + strlen (aux_info_suffix) + 1);
  char *aux_info_base;
  char *aux_info_limit;
  char *aux_info_relocated_name;
  const char *aux_info_second_line;
  time_t aux_info_mtime;
  size_t aux_info_size;
  int must_create;

  /* Construct the aux_info filename from the base source filename.  */

  strcpy (aux_info_filename, base_source_filename);
  strcat (aux_info_filename, aux_info_suffix);

  /* Check that the aux_info file exists and is readable.  If it does not
     exist, try to create it (once only).  */

  /* If file doesn't exist, set must_create.
     Likewise if it exists and we can read it but it is obsolete.
     Otherwise, report an error.  */
  must_create = 0;

  /* Come here with must_create set to 1 if file is out of date.  */
start_over: ;

  if (access (aux_info_filename, R_OK) == -1)
    {
      if (errno == ENOENT)
	{
	  if (is_syscalls)
	    {
	      notice ("%s: warning: missing SYSCALLS file '%s'\n",
		      pname, aux_info_filename);
	      return;
	    }
	  must_create = 1;
	}
      else
	{
	  int errno_val = errno;
	  notice ("%s: can't read aux info file '%s': %s\n",
		  pname, shortpath (NULL, aux_info_filename),
		  xstrerror (errno_val));
	  errors++;
	  return;
	}
    }
#if 0 /* There is code farther down to take care of this.  */
  else
    {
      struct stat s1, s2;
      stat (aux_info_file_name, &s1);
      stat (base_source_file_name, &s2);
      if (s2.st_mtime > s1.st_mtime)
	must_create = 1;
    }
#endif /* 0 */

  /* If we need a .X file, create it, and verify we can read it.  */
  if (must_create)
    {
      if (!gen_aux_info_file (base_source_filename))
	{
	  errors++;
	  return;
	}
      if (access (aux_info_filename, R_OK) == -1)
	{
	  int errno_val = errno;
	  notice ("%s: can't read aux info file '%s': %s\n",
		  pname, shortpath (NULL, aux_info_filename),
		  xstrerror (errno_val));
	  errors++;
	  return;
	}
    }

  {
    struct stat stat_buf;

    /* Get some status information about this aux_info file.  */

    if (stat (aux_info_filename, &stat_buf) == -1)
      {
	int errno_val = errno;
	notice ("%s: can't get status of aux info file '%s': %s\n",
		pname, shortpath (NULL, aux_info_filename),
		xstrerror (errno_val));
	errors++;
	return;
      }

    /* Check on whether or not this aux_info file is zero length.  If it is,
       then just ignore it and return.  */

    if ((aux_info_size = stat_buf.st_size) == 0)
      return;

    /* Get the date/time of last modification for this aux_info file and
       remember it.  We will have to check that any source files that it
       contains information about are at least this old or older.  */

    aux_info_mtime = stat_buf.st_mtime;

    if (!is_syscalls)
      {
	/* Compare mod time with the .c file; update .X file if obsolete.
	   The code later on can fail to check the .c file
	   if it did not directly define any functions.  */

	if (stat (base_source_filename, &stat_buf) == -1)
	  {
	    int errno_val = errno;
	    notice ("%s: can't get status of aux info file '%s': %s\n",
		    pname, shortpath (NULL, base_source_filename),
		    xstrerror (errno_val));
	    errors++;
	    return;
	  }
	if (stat_buf.st_mtime > aux_info_mtime)
	  {
	    must_create = 1;
	    goto start_over;
	  }
      }
  }

  {
    int aux_info_file;
    int fd_flags;

    /* Open the aux_info file.  */

    fd_flags = O_RDONLY;
#ifdef O_BINARY
    /* Use binary mode to avoid having to deal with different EOL characters.  */
    fd_flags |= O_BINARY;
#endif
    if ((aux_info_file = open (aux_info_filename, fd_flags, 0444 )) == -1)
      {
	int errno_val = errno;
	notice ("%s: can't open aux info file '%s' for reading: %s\n",
		pname, shortpath (NULL, aux_info_filename),
		xstrerror (errno_val));
	return;
      }

    /* Allocate space to hold the aux_info file in memory.  */

    aux_info_base = xmalloc (aux_info_size + 1);
    aux_info_limit = aux_info_base + aux_info_size;
    *aux_info_limit = '\0';

    /* Read the aux_info file into memory.  */

    if (safe_read (aux_info_file, aux_info_base, aux_info_size) !=
	(int) aux_info_size)
      {
	int errno_val = errno;
	notice ("%s: error reading aux info file '%s': %s\n",
		pname, shortpath (NULL, aux_info_filename),
		xstrerror (errno_val));
	free (aux_info_base);
	close (aux_info_file);
	return;
      }

    /* Close the aux info file.  */

    if (close (aux_info_file))
      {
	int errno_val = errno;
	notice ("%s: error closing aux info file '%s': %s\n",
		pname, shortpath (NULL, aux_info_filename),
		xstrerror (errno_val));
	free (aux_info_base);
	close (aux_info_file);
	return;
      }
  }

  /* Delete the aux_info file (unless requested not to).  If the deletion
     fails for some reason, don't even worry about it.  */

  if (must_create && !keep_it)
    if (unlink (aux_info_filename) == -1)
      {
	int errno_val = errno;
	notice ("%s: can't delete aux info file '%s': %s\n",
		pname, shortpath (NULL, aux_info_filename),
		xstrerror (errno_val));
      }

  /* Save a pointer into the first line of the aux_info file which
     contains the filename of the directory from which the compiler
     was invoked when the associated source file was compiled.
     This information is used later to help create complete
     filenames out of the (potentially) relative filenames in
     the aux_info file.  */

  {
    char *p = aux_info_base;

    while (*p != ':'
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
	   || (*p == ':' && *p && *(p+1) && IS_DIR_SEPARATOR (*(p+1)))
#endif
	   )
      p++;
    p++;
    while (*p == ' ')
      p++;
    invocation_filename = p;	/* Save a pointer to first byte of path.  */
    while (*p != ' ')
      p++;
    *p++ = DIR_SEPARATOR;
    *p++ = '\0';
    while (*p++ != '\n')
      continue;
    aux_info_second_line = p;
    aux_info_relocated_name = 0;
    if (! IS_ABSOLUTE_PATH (invocation_filename))
      {
	/* INVOCATION_FILENAME is relative;
	   append it to BASE_SOURCE_FILENAME's dir.  */
	char *dir_end;
	aux_info_relocated_name = xmalloc (base_len + (p-invocation_filename));
	strcpy (aux_info_relocated_name, base_source_filename);
	dir_end = strrchr (aux_info_relocated_name, DIR_SEPARATOR);
#ifdef DIR_SEPARATOR_2
	{
	  char *slash;

	  slash = strrchr (dir_end ? dir_end : aux_info_relocated_name,
			   DIR_SEPARATOR_2);
	  if (slash)
	    dir_end = slash;
	}
#endif
	if (dir_end)
	  dir_end++;
	else
	  dir_end = aux_info_relocated_name;
	strcpy (dir_end, invocation_filename);
	invocation_filename = aux_info_relocated_name;
      }
  }


  {
    const char *aux_info_p;

    /* Do a pre-pass on the lines in the aux_info file, making sure that all
       of the source files referenced in there are at least as old as this
       aux_info file itself.  If not, go back and regenerate the aux_info
       file anew.  Don't do any of this for the syscalls file.  */

    if (!is_syscalls)
      {
	current_aux_info_lineno = 2;

	for (aux_info_p = aux_info_second_line; *aux_info_p; )
	  {
	    if (referenced_file_is_newer (aux_info_p, aux_info_mtime))
	      {
		free (aux_info_base);
		free (aux_info_relocated_name);
		if (keep_it && unlink (aux_info_filename) == -1)
		  {
		    int errno_val = errno;
	            notice ("%s: can't delete file '%s': %s\n",
			    pname, shortpath (NULL, aux_info_filename),
			    xstrerror (errno_val));
	            return;
	          }
		must_create = 1;
	        goto start_over;
	      }

	    /* Skip over the rest of this line to start of next line.  */

	    while (*aux_info_p != '\n')
	      aux_info_p++;
	    aux_info_p++;
	    current_aux_info_lineno++;
	  }
      }

    /* Now do the real pass on the aux_info lines.  Save their information in
       the in-core data base.  */

    current_aux_info_lineno = 2;

    for (aux_info_p = aux_info_second_line; *aux_info_p;)
      {
	char *unexpanded_line = unexpand_if_needed (aux_info_p);

	if (unexpanded_line)
	  {
	    save_def_or_dec (unexpanded_line, is_syscalls);
	    free (unexpanded_line);
	  }
	else
	  save_def_or_dec (aux_info_p, is_syscalls);

	/* Skip over the rest of this line and get to start of next line.  */

	while (*aux_info_p != '\n')
	  aux_info_p++;
	aux_info_p++;
	current_aux_info_lineno++;
      }
  }

  free (aux_info_base);
  free (aux_info_relocated_name);
}