#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* to_sections; int /*<<< orphan*/ * to_sections_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_SOLIB () ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * core_bfd ; 
 int /*<<< orphan*/ * core_gdbarch ; 
 TYPE_1__ core_ops ; 
 int /*<<< orphan*/ * core_vec ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  warning (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
core_close (int quitting)
{
  char *name;

  if (core_bfd)
    {
      inferior_ptid = null_ptid;	/* Avoid confusion from thread stuff */

      /* Clear out solib state while the bfd is still open. See
         comments in clear_solib in solib.c. */
#ifdef CLEAR_SOLIB
      CLEAR_SOLIB ();
#endif

      name = bfd_get_filename (core_bfd);
      if (!bfd_close (core_bfd))
	warning ("cannot close \"%s\": %s",
		 name, bfd_errmsg (bfd_get_error ()));
      xfree (name);
      core_bfd = NULL;
      if (core_ops.to_sections)
	{
	  xfree (core_ops.to_sections);
	  core_ops.to_sections = NULL;
	  core_ops.to_sections_end = NULL;
	}
    }
  core_vec = NULL;
  core_gdbarch = NULL;
}