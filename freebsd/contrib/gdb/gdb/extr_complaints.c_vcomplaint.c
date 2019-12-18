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
typedef  int /*<<< orphan*/  va_list ;
struct complaints {int series; TYPE_1__* explanation; } ;
struct complain {scalar_t__ counter; int /*<<< orphan*/  fmt; int /*<<< orphan*/  line; int /*<<< orphan*/ * file; } ;
struct cleanup {int dummy; } ;
typedef  enum complaint_series { ____Placeholder_complaint_series } complaint_series ;
struct TYPE_2__ {int /*<<< orphan*/  postfix; int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
#define  FIRST_MESSAGE 131 
#define  ISOLATED_MESSAGE 130 
#define  SHORT_FIRST_MESSAGE 129 
#define  SUBSEQUENT_MESSAGE 128 
 int /*<<< orphan*/  begin_line () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct complain* find_complaint (struct complaints*,char const*,int,char const*) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 struct complaints* get_complaints (struct complaints**) ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  internal_vwarning (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ stop_whining ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vwarning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xvasprintf (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vcomplaint (struct complaints **c, const char *file, int line, const char *fmt,
	    va_list args)
{
  struct complaints *complaints = get_complaints (c);
  struct complain *complaint = find_complaint (complaints, file, line, fmt);
  enum complaint_series series;
  gdb_assert (complaints != NULL);

  complaint->counter++;
  if (complaint->counter > stop_whining)
    return;

  if (info_verbose)
    series = SUBSEQUENT_MESSAGE;
  else
    series = complaints->series;

  if (complaint->file != NULL)
    internal_vwarning (complaint->file, complaint->line, complaint->fmt, args);
  else if (warning_hook)
    (*warning_hook) (complaint->fmt, args);
  else
    {
      if (complaints->explanation == NULL)
	/* A [v]warning() call always appends a newline.  */
	vwarning (complaint->fmt, args);
      else
	{
	  char *msg;
	  struct cleanup *cleanups;
	  xvasprintf (&msg, complaint->fmt, args);
	  cleanups = make_cleanup (xfree, msg);
	  wrap_here ("");
	  if (series != SUBSEQUENT_MESSAGE)
	    begin_line ();
	  fprintf_filtered (gdb_stderr, "%s%s%s",
			    complaints->explanation[series].prefix, msg,
			    complaints->explanation[series].postfix);
	  /* Force a line-break after any isolated message.  For the
             other cases, clear_complaints() takes care of any missing
             trailing newline, the wrap_here() is just a hint.  */
	  if (series == ISOLATED_MESSAGE)
	    /* It would be really nice to use begin_line() here.
	       Unfortunately that function doesn't track GDB_STDERR and
	       consequently will sometimes supress a line when it
	       shouldn't.  */
	    fputs_filtered ("\n", gdb_stderr);
	  else
	    wrap_here ("");
	  do_cleanups (cleanups);
	}
    }

  switch (series)
    {
    case ISOLATED_MESSAGE:
      break;
    case FIRST_MESSAGE:
      complaints->series = SUBSEQUENT_MESSAGE;
      break;
    case SUBSEQUENT_MESSAGE:
    case SHORT_FIRST_MESSAGE:
      complaints->series = SUBSEQUENT_MESSAGE;
      break;
    }

  /* If GDB dumps core, we'd like to see the complaints first.
     Presumably GDB will not be sending so many complaints that this
     becomes a performance hog.  */

  gdb_flush (gdb_stderr);
}