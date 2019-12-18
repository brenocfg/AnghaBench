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
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  mips_expect (char*) ; 
 int /*<<< orphan*/  remove (int /*<<< orphan*/ ) ; 
 scalar_t__ tftp_in_use ; 
 int /*<<< orphan*/  tftp_localname ; 

__attribute__((used)) static int
mips_expect_download (char *string)
{
  if (!mips_expect (string))
    {
      fprintf_unfiltered (gdb_stderr, "Load did not complete successfully.\n");
      if (tftp_in_use)
	remove (tftp_localname);	/* Remove temporary file */
      return 0;
    }
  else
    return 1;
}