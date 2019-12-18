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
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_close (scalar_t__) ; 
 int /*<<< orphan*/  bfd_get_filename (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  maybequit () ; 
 scalar_t__ obfd ; 
 char* program_name ; 
 int /*<<< orphan*/  real_name ; 
 int /*<<< orphan*/  smart_rename (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

void
ar_save (void)
{
  if (!obfd)
    {
      fprintf (stderr, _("%s: no open output archive\n"), program_name);
      maybequit ();
    }
  else
    {
      char *ofilename = xstrdup (bfd_get_filename (obfd));

      bfd_close (obfd);

      smart_rename (ofilename, real_name, 0);
      obfd = 0;
      free (ofilename);
    }
}