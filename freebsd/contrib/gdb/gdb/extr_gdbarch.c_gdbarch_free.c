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
struct obstack {int dummy; } ;
struct gdbarch {struct obstack* obstack; int /*<<< orphan*/  initialized_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  obstack_free (struct obstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (struct obstack*) ; 

void
gdbarch_free (struct gdbarch *arch)
{
  struct obstack *obstack;
  gdb_assert (arch != NULL);
  gdb_assert (!arch->initialized_p);
  obstack = arch->obstack;
  obstack_free (obstack, 0); /* Includes the ARCH.  */
  xfree (obstack);
}