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
 int /*<<< orphan*/  INSTALLDIR ; 
 int /*<<< orphan*/  INSTALLPREFIX ; 
 int /*<<< orphan*/  activate_libdirs () ; 
 char* add_dotbin (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execv (char*,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 char* get_full_program_name () ; 
 char* program_name ; 
 int /*<<< orphan*/  relocate_libdirs () ; 
 int /*<<< orphan*/  set_program_name_and_installdir (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

int
main (int argc, char *argv[])
{
  char *full_program_name;

  /* Set the program name and perform preparations for
     get_full_program_name() and relocate().  */
  set_program_name_and_installdir (argv[0], INSTALLPREFIX, INSTALLDIR);

  /* Get the full program path.  (Important if accessed through a symlink.)  */
  full_program_name = get_full_program_name ();
  if (full_program_name == NULL)
    full_program_name = argv[0];

  /* Invoke the real program, with suffix ".bin".  */
  argv[0] = add_dotbin (full_program_name);
  relocate_libdirs ();
  activate_libdirs ();
  execv (argv[0], argv);
  fprintf (stderr, "%s: could not execute %s: %s\n",
           program_name, argv[0], strerror (errno));
  exit (127);
}