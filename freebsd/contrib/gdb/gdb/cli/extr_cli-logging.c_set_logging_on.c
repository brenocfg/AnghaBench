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
 int /*<<< orphan*/  handle_redirections (int) ; 
 int /*<<< orphan*/  logging_filename ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
set_logging_on (char *args, int from_tty)
{
  char *rest = args;
  if (rest && *rest)
    {
      xfree (logging_filename);
      logging_filename = xstrdup (rest);
    }
  handle_redirections (from_tty);
}