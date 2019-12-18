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
 int /*<<< orphan*/  END_PROGRESS (char*) ; 
 scalar_t__ FILENAME_CMP (char*,char*) ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  LOCALS_UNDEF ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  START_PROGRESS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_UNDEF ; 
 int /*<<< orphan*/  bfd_init () ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_main (int,char**) ; 
 int /*<<< orphan*/  discard_locals ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int is_strip ; 
 char* program_name ; 
 int /*<<< orphan*/  set_default_bfd_target () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int status ; 
 int /*<<< orphan*/  strip_main (int,char**) ; 
 int /*<<< orphan*/  strip_symbols ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc_set_program_name (char*) ; 

int
main (int argc, char *argv[])
{
#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  program_name = argv[0];
  xmalloc_set_program_name (program_name);

  START_PROGRESS (program_name, 0);

  expandargv (&argc, &argv);

  strip_symbols = STRIP_UNDEF;
  discard_locals = LOCALS_UNDEF;

  bfd_init ();
  set_default_bfd_target ();

  if (is_strip < 0)
    {
      int i = strlen (program_name);
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      /* Drop the .exe suffix, if any.  */
      if (i > 4 && FILENAME_CMP (program_name + i - 4, ".exe") == 0)
	{
	  i -= 4;
	  program_name[i] = '\0';
	}
#endif
      is_strip = (i >= 5 && FILENAME_CMP (program_name + i - 5, "strip") == 0);
    }

  if (is_strip)
    strip_main (argc, argv);
  else
    copy_main (argc, argv);

  END_PROGRESS (program_name);

  return status;
}