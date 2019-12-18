#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ style; } ;
struct TYPE_4__ {TYPE_1__ deps; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DEPS_NONE ; 
 scalar_t__ cpp_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* cpp_opts ; 
 scalar_t__ deps_append ; 
 int /*<<< orphan*/  deps_file ; 
 int /*<<< orphan*/  errorcount ; 
 int /*<<< orphan*/  fatal_error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  out_fname ; 
 int /*<<< orphan*/ * out_stream ; 
 int /*<<< orphan*/  parse_in ; 

void
c_common_finish (void)
{
  FILE *deps_stream = NULL;

  if (cpp_opts->deps.style != DEPS_NONE)
    {
      /* If -M or -MM was seen without -MF, default output to the
	 output stream.  */
      if (!deps_file)
	deps_stream = out_stream;
      else
	{
	  deps_stream = fopen (deps_file, deps_append ? "a": "w");
	  if (!deps_stream)
	    fatal_error ("opening dependency file %s: %m", deps_file);
	}
    }

  /* For performance, avoid tearing down cpplib's internal structures
     with cpp_destroy ().  */
  errorcount += cpp_finish (parse_in, deps_stream);

  if (deps_stream && deps_stream != out_stream
      && (ferror (deps_stream) || fclose (deps_stream)))
    fatal_error ("closing dependency file %s: %m", deps_file);

  if (out_stream && (ferror (out_stream) || fclose (out_stream)))
    fatal_error ("when writing output to %s: %m", out_fname);
}