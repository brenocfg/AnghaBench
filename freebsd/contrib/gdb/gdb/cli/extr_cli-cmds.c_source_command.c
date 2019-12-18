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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RT ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  script_from_file (int /*<<< orphan*/ *,char*) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  xfree ; 

void
source_command (char *args, int from_tty)
{
  FILE *stream;
  struct cleanup *old_cleanups;
  char *file = args;

  if (file == NULL)
    {
      error ("source command requires pathname of file to source.");
    }

  file = tilde_expand (file);
  old_cleanups = make_cleanup (xfree, file);

  stream = fopen (file, FOPEN_RT);
  if (!stream)
    {
      if (from_tty)
	perror_with_name (file);
      else
	return;
    }

  script_from_file (stream, file);

  do_cleanups (old_cleanups);
}