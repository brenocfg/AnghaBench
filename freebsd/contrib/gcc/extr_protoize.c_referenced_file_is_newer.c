#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_3__ {scalar_t__ mtime; } ;
typedef  TYPE_1__ file_info ;

/* Variables and functions */
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 int /*<<< orphan*/  abspath (int /*<<< orphan*/ ,char*) ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  check_aux_info (int) ; 
 TYPE_1__* find_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invocation_filename ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static int
referenced_file_is_newer (const char *l, time_t aux_info_mtime)
{
  const char *p;
  file_info *fi_p;
  char *filename;

  check_aux_info (l[0] == '/');
  check_aux_info (l[1] == '*');
  check_aux_info (l[2] == ' ');

  {
    const char *filename_start = p = l + 3;

    while (*p != ':'
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
	   || (*p == ':' && *p && *(p+1) && IS_DIR_SEPARATOR (*(p+1)))
#endif
	   )
      p++;
    filename = alloca ((size_t) (p - filename_start) + 1);
    strncpy (filename, filename_start, (size_t) (p - filename_start));
    filename[p-filename_start] = '\0';
  }

  /* Call find_file to find the file_info record associated with the file
     which contained this particular def or dec item.  Note that this call
     may cause a new file_info record to be created if this is the first time
     that we have ever known about this particular file.  */

  fi_p = find_file (abspath (invocation_filename, filename), 0);

  return (fi_p->mtime > aux_info_mtime);
}