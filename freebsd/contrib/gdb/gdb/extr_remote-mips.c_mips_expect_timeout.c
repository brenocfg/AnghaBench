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

/* Variables and functions */
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc_readable (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_readable (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  immediate_quit ; 
 int /*<<< orphan*/  mips_desc ; 
 scalar_t__ remote_debug ; 
 int serial_readchar (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mips_expect_timeout (const char *string, int timeout)
{
  const char *p = string;

  if (remote_debug)
    {
      fprintf_unfiltered (gdb_stdlog, "Expected \"");
      fputs_readable (string, gdb_stdlog);
      fprintf_unfiltered (gdb_stdlog, "\", got \"");
    }

  immediate_quit++;
  while (1)
    {
      int c;

      /* Must use serial_readchar() here cuz mips_readchar would get
	 confused if we were waiting for the mips_monitor_prompt... */

      c = serial_readchar (mips_desc, timeout);

      if (c == SERIAL_TIMEOUT)
	{
	  if (remote_debug)
	    fprintf_unfiltered (gdb_stdlog, "\": FAIL\n");
	  return 0;
	}

      if (remote_debug)
	fputc_readable (c, gdb_stdlog);

      if (c == *p++)
	{
	  if (*p == '\0')
	    {
	      immediate_quit--;
	      if (remote_debug)
		fprintf_unfiltered (gdb_stdlog, "\": OK\n");
	      return 1;
	    }
	}
      else
	{
	  p = string;
	  if (c == *p)
	    p++;
	}
    }
}