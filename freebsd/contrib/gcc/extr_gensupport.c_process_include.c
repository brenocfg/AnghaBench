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
struct file_name_list {int /*<<< orphan*/  fname; struct file_name_list* next; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DIR_SEPARATOR 128 
 int /*<<< orphan*/  IS_ABSOLUTE_PATH (char const*) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ base_dir ; 
 char* concat (scalar_t__,char const*,char const*,...) ; 
 int errors ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 struct file_name_list* first_dir_md_include ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  include_callback (char*) ; 
 int /*<<< orphan*/  message_with_line (int,char*,char const*) ; 
 int /*<<< orphan*/  process_rtx (int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_rtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 char const* read_rtx_filename ; 
 int read_rtx_lineno ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
process_include (rtx desc, int lineno)
{
  const char *filename = XSTR (desc, 0);
  const char *old_filename;
  int old_lineno;
  char *pathname;
  FILE *input_file;

  /* If specified file name is absolute, skip the include stack.  */
  if (! IS_ABSOLUTE_PATH (filename))
    {
      struct file_name_list *stackp;

      /* Search directory path, trying to open the file.  */
      for (stackp = first_dir_md_include; stackp; stackp = stackp->next)
	{
	  static const char sep[2] = { DIR_SEPARATOR, '\0' };

	  pathname = concat (stackp->fname, sep, filename, NULL);
	  input_file = fopen (pathname, "r");
	  if (input_file != NULL)
	    goto success;
	  free (pathname);
	}
    }

  if (base_dir)
    pathname = concat (base_dir, filename, NULL);
  else
    pathname = xstrdup (filename);
  input_file = fopen (pathname, "r");
  if (input_file == NULL)
    {
      free (pathname);
      message_with_line (lineno, "include file `%s' not found", filename);
      errors = 1;
      return;
    }
 success:

  /* Save old cursor; setup new for the new file.  Note that "lineno" the
     argument to this function is the beginning of the include statement,
     while read_rtx_lineno has already been advanced.  */
  old_filename = read_rtx_filename;
  old_lineno = read_rtx_lineno;
  read_rtx_filename = pathname;
  read_rtx_lineno = 1;

  if (include_callback)
    include_callback (pathname);

  /* Read the entire file.  */
  while (read_rtx (input_file, &desc, &lineno))
    process_rtx (desc, lineno);

  /* Do not free pathname.  It is attached to the various rtx queue
     elements.  */

  read_rtx_filename = old_filename;
  read_rtx_lineno = old_lineno;

  fclose (input_file);
}