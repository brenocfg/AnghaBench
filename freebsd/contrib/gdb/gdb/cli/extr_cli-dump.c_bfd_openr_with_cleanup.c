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
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char const*,char const*) ; 
 int /*<<< orphan*/  error (char*,char const*,...) ; 
 int /*<<< orphan*/  make_cleanup_bfd_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd *
bfd_openr_with_cleanup (const char *filename, const char *target)
{
  bfd *ibfd;

  ibfd = bfd_openr (filename, target);
  if (ibfd == NULL)
    error ("Failed to open %s: %s.", filename, 
	   bfd_errmsg (bfd_get_error ()));

  make_cleanup_bfd_close (ibfd);
  if (!bfd_check_format (ibfd, bfd_object))
    error ("'%s' is not a recognized file format.", filename);

  return ibfd;
}