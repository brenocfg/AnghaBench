#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* line_table; int /*<<< orphan*/  main_file; int /*<<< orphan*/  no_search_path; scalar_t__ deps; } ;
typedef  TYPE_3__ cpp_reader ;
struct TYPE_13__ {int /*<<< orphan*/  style; } ;
struct TYPE_11__ {int used; TYPE_1__* maps; } ;
struct TYPE_10__ {char* to_file; } ;

/* Variables and functions */
 scalar_t__ CPP_OPTION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEPS_NONE ; 
 scalar_t__ _cpp_find_failed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_find_file (TYPE_3__*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_stack_file (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__ deps ; 
 int /*<<< orphan*/  deps_add_default_target (scalar_t__,char const*) ; 
 scalar_t__ deps_init () ; 
 int /*<<< orphan*/  preprocessed ; 
 int /*<<< orphan*/  read_original_filename (TYPE_3__*) ; 

const char *
cpp_read_main_file (cpp_reader *pfile, const char *fname)
{
  if (CPP_OPTION (pfile, deps.style) != DEPS_NONE)
    {
      if (!pfile->deps)
	pfile->deps = deps_init ();

      /* Set the default target (if there is none already).  */
      deps_add_default_target (pfile->deps, fname);
    }

  pfile->main_file
    = _cpp_find_file (pfile, fname, &pfile->no_search_path, false, 0);
  if (_cpp_find_failed (pfile->main_file))
    return NULL;

  _cpp_stack_file (pfile, pfile->main_file, false);

  /* For foo.i, read the original filename foo.c now, for the benefit
     of the front ends.  */
  if (CPP_OPTION (pfile, preprocessed))
    {
      read_original_filename (pfile);
      fname = pfile->line_table->maps[pfile->line_table->used-1].to_file;
    }
  return fname;
}