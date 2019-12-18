#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct cpp_dir {int dummy; } ;
typedef  enum include_type { ____Placeholder_include_type } include_type ;
struct TYPE_11__ {TYPE_2__* buffer; struct cpp_dir* quote_include; scalar_t__ quote_ignores_source_dir; struct cpp_dir* bracket_include; TYPE_4__* main_file; struct cpp_dir no_search_path; } ;
typedef  TYPE_3__ cpp_reader ;
typedef  struct cpp_dir cpp_dir ;
struct TYPE_12__ {TYPE_1__* dir; } ;
typedef  TYPE_4__ _cpp_file ;
struct TYPE_10__ {int sysp; TYPE_4__* file; } ;
struct TYPE_9__ {struct cpp_dir* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ IS_ABSOLUTE_PATH (char const*) ; 
 int IT_CMDLINE ; 
 int IT_INCLUDE_NEXT ; 
 int /*<<< orphan*/  cpp_error (TYPE_3__*,int /*<<< orphan*/ ,char*,char const*) ; 
 char* dir_name_of_file (TYPE_4__*) ; 
 struct cpp_dir* make_cpp_dir (TYPE_3__*,char*,int) ; 

__attribute__((used)) static struct cpp_dir *
search_path_head (cpp_reader *pfile, const char *fname, int angle_brackets,
		  enum include_type type)
{
  cpp_dir *dir;
  _cpp_file *file;

  if (IS_ABSOLUTE_PATH (fname))
    return &pfile->no_search_path;

  /* pfile->buffer is NULL when processing an -include command-line flag.  */
  file = pfile->buffer == NULL ? pfile->main_file : pfile->buffer->file;

  /* For #include_next, skip in the search path past the dir in which
     the current file was found, but if it was found via an absolute
     path use the normal search logic.  */
  if (type == IT_INCLUDE_NEXT && file->dir)
    dir = file->dir->next;
  else if (angle_brackets)
    dir = pfile->bracket_include;
  else if (type == IT_CMDLINE)
    /* -include and -imacros use the #include "" chain with the
       preprocessor's cwd prepended.  */
    return make_cpp_dir (pfile, "./", false);
  else if (pfile->quote_ignores_source_dir)
    dir = pfile->quote_include;
  else
    return make_cpp_dir (pfile, dir_name_of_file (file),
			 pfile->buffer ? pfile->buffer->sysp : 0);

  if (dir == NULL)
    cpp_error (pfile, CPP_DL_ERROR,
	       "no include path in which to search for %s", fname);

  return dir;
}