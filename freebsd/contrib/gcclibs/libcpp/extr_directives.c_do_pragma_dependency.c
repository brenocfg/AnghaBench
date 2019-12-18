#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 scalar_t__ CPP_EOF ; 
 int /*<<< orphan*/  _cpp_backup_tokens (int /*<<< orphan*/ *,int) ; 
 int _cpp_compare_file_date (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* cpp_get_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_diagnostic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 char* parse_include (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_pragma_dependency (cpp_reader *pfile)
{
  const char *fname;
  int angle_brackets, ordering;

  fname = parse_include (pfile, &angle_brackets, NULL);
  if (!fname)
    return;

  ordering = _cpp_compare_file_date (pfile, fname, angle_brackets);
  if (ordering < 0)
    cpp_error (pfile, CPP_DL_WARNING, "cannot find source file %s", fname);
  else if (ordering > 0)
    {
      cpp_error (pfile, CPP_DL_WARNING,
		 "current file is older than %s", fname);
      if (cpp_get_token (pfile)->type != CPP_EOF)
	{
	  _cpp_backup_tokens (pfile, 1);
	  do_diagnostic (pfile, CPP_DL_WARNING, 0);
	}
    }

  free ((void *) fname);
}