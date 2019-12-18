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
 int /*<<< orphan*/  Adp_SetLogfile (scalar_t__) ; 
 scalar_t__ log_filename ; 
 int /*<<< orphan*/  printf_filtered (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xfree (scalar_t__) ; 
 scalar_t__ xstrdup (char*) ; 

__attribute__((used)) static void 
rdilogfile_command (char *arg, int from_tty)
{
  if (!arg || strlen (arg) == 0)
    {
      printf_filtered ("rdi log file is '%s'\n", log_filename);
      return;
    }

  if (log_filename)
    xfree (log_filename);

  log_filename = xstrdup (arg);

  Adp_SetLogfile (log_filename);
}