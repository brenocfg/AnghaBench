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
struct filedep {char* pathname; struct filedep* next; } ;

/* Variables and functions */
 int FATAL_EXIT_CODE ; 
 scalar_t__ SUCCESS_EXIT_CODE ; 
 int /*<<< orphan*/  add_filedep ; 
 struct filedep* deps ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  include_callback ; 
 scalar_t__ init_md_reader_args (int,char**) ; 
 int /*<<< orphan*/ ** last ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  struct filedep *d;

  progname = "genmddeps";
  include_callback = add_filedep;
  
  if (init_md_reader_args (argc, argv) != SUCCESS_EXIT_CODE)
    return (FATAL_EXIT_CODE);

  *last = NULL;

  /* Output a variable containing all of the include files.  */
  fputs ("MD_INCLUDES =", stdout);
  for (d = deps; d ; d = d->next)
    printf (" \\\n\t%s", d->pathname);
  putchar ('\n');

  /* Output make targets for these includes with empty actions.  This
     will guard against make errors when includes are removed.  */
  for (d = deps; d ; d = d->next)
    printf ("\n%s:\n", d->pathname);

  fflush (stdout);
  return (ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE);
}