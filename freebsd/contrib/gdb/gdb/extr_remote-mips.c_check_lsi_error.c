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
struct lsi_error {int code; int string; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int W_WARN ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 struct lsi_error* lsi_error_table ; 
 struct lsi_error* lsi_warning_table ; 
 scalar_t__ monitor_warnings ; 
 char* paddr_nz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_lsi_error (CORE_ADDR addr, int rerrflg)
{
  struct lsi_error *err;
  char *saddr = paddr_nz (addr);	/* printable address string */

  if (rerrflg == 0)		/* no error */
    return 0;

  /* Warnings can be ORed together, so check them all.  */
  if (rerrflg & W_WARN)
    {
      if (monitor_warnings)
	{
	  int found = 0;
	  for (err = lsi_warning_table; err->code != 0; err++)
	    {
	      if ((err->code & rerrflg) == err->code)
		{
		  found = 1;
		  fprintf_unfiltered (gdb_stderr,
				  "common_breakpoint (0x%s): Warning: %s\n",
				      saddr,
				      err->string);
		}
	    }
	  if (!found)
	    fprintf_unfiltered (gdb_stderr,
			"common_breakpoint (0x%s): Unknown warning: 0x%x\n",
				saddr,
				rerrflg);
	}
      return 0;
    }

  /* Errors are unique, i.e. can't be ORed together.  */
  for (err = lsi_error_table; err->code != 0; err++)
    {
      if ((err->code & rerrflg) == err->code)
	{
	  fprintf_unfiltered (gdb_stderr,
			      "common_breakpoint (0x%s): Error: %s\n",
			      saddr,
			      err->string);
	  return 1;
	}
    }
  fprintf_unfiltered (gdb_stderr,
		      "common_breakpoint (0x%s): Unknown error: 0x%x\n",
		      saddr,
		      rerrflg);
  return 1;
}