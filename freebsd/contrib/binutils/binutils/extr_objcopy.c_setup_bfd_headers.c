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
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_copy_private_header_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  non_fatal (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int status ; 

__attribute__((used)) static void
setup_bfd_headers (bfd *ibfd, bfd *obfd)
{
  const char *err;

  /* Allow the BFD backend to copy any private data it understands
     from the input section to the output section.  */
  if (! bfd_copy_private_header_data (ibfd, obfd))
    {
      err = _("private header data");
      goto loser;
    }

  /* All went well.  */
  return;

loser:
  non_fatal (_("%s: error in %s: %s"),
	     bfd_get_filename (ibfd),
	     err, bfd_errmsg (bfd_get_error ()));
  status = 1;
}