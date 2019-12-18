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
struct gdbarch {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  deprecated_current_gdbarch_select_hack (struct gdbarch*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct gdbarch* gdbarch_from_bfd (int /*<<< orphan*/ *) ; 

void
set_gdbarch_from_file (bfd *abfd)
{
  struct gdbarch *gdbarch;

  gdbarch = gdbarch_from_bfd (abfd);
  if (gdbarch == NULL)
    error ("Architecture of file not recognized.\n");
  deprecated_current_gdbarch_select_hack (gdbarch);
}