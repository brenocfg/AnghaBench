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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 scalar_t__ export_all_symbols ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_all_symbols (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_drectve_symbols (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scan_open_obj_file (bfd *abfd)
{
  if (export_all_symbols)
    scan_all_symbols (abfd);
  else
    scan_drectve_symbols (abfd);

  /* FIXME: we ought to read in and block out the base relocations.  */

  /* xgettext:c-format */
  inform (_("Done reading %s"), bfd_get_filename (abfd));
}