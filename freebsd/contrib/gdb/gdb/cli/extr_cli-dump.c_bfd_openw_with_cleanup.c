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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openw (char*,char const*) ; 
 int /*<<< orphan*/  bfd_set_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  make_cleanup_bfd_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd *
bfd_openw_with_cleanup (char *filename, const char *target, char *mode)
{
  bfd *obfd;

  if (*mode == 'w')	/* Write: create new file */
    {
      obfd = bfd_openw (filename, target);
      if (obfd == NULL)
	error ("Failed to open %s: %s.", filename, 
	       bfd_errmsg (bfd_get_error ()));
      make_cleanup_bfd_close (obfd);
      if (!bfd_set_format (obfd, bfd_object))
	error ("bfd_openw_with_cleanup: %s.", bfd_errmsg (bfd_get_error ()));
    }
  else if (*mode == 'a')	/* Append to existing file */
    {	/* FIXME -- doesn't work... */
      error ("bfd_openw does not work with append.");
    }
  else
    error ("bfd_openw_with_cleanup: unknown mode %s.", mode);

  return obfd;
}