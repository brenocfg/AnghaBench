#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  source_location ;
struct TYPE_6__ {int /*<<< orphan*/  errors; } ;
typedef  TYPE_1__ cpp_reader ;

/* Variables and functions */
#define  CPP_DL_ERROR 132 
 int CPP_DL_EXTRACT (int) ; 
#define  CPP_DL_ICE 131 
#define  CPP_DL_PEDWARN 130 
#define  CPP_DL_WARNING 129 
 scalar_t__ CPP_DL_WARNING_P (int) ; 
#define  CPP_DL_WARNING_SYSHDR 128 
 int /*<<< orphan*/  CPP_OPTION (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cpp_in_system_header (TYPE_1__*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inhibit_errors ; 
 int /*<<< orphan*/  inhibit_warnings ; 
 int /*<<< orphan*/  pedantic_errors ; 
 int /*<<< orphan*/  print_location (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn_system_headers ; 
 int /*<<< orphan*/  warnings_are_errors ; 

int
_cpp_begin_message (cpp_reader *pfile, int code,
		    source_location src_loc, unsigned int column)
{
  int level = CPP_DL_EXTRACT (code);

  switch (level)
    {
    case CPP_DL_WARNING:
    case CPP_DL_PEDWARN:
      if (cpp_in_system_header (pfile)
	  && ! CPP_OPTION (pfile, warn_system_headers))
	return 0;
      /* Fall through.  */

    case CPP_DL_WARNING_SYSHDR:
      if (CPP_OPTION (pfile, warnings_are_errors)
	  || (level == CPP_DL_PEDWARN && CPP_OPTION (pfile, pedantic_errors)))
	{
	  if (CPP_OPTION (pfile, inhibit_errors))
	    return 0;
	  level = CPP_DL_ERROR;
	  pfile->errors++;
	}
      else if (CPP_OPTION (pfile, inhibit_warnings))
	return 0;
      break;

    case CPP_DL_ERROR:
      if (CPP_OPTION (pfile, inhibit_errors))
	return 0;
      /* ICEs cannot be inhibited.  */
    case CPP_DL_ICE:
      pfile->errors++;
      break;
    }

  print_location (pfile, src_loc, column);
  if (CPP_DL_WARNING_P (level))
    fputs (_("warning: "), stderr);
  else if (level == CPP_DL_ICE)
    fputs (_("internal error: "), stderr);
  else
    fputs (_("error: "), stderr);

  return 1;
}