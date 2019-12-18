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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
i386_svr4_pc_in_sigtramp (CORE_ADDR pc, char *name)
{
  /* UnixWare uses _sigacthandler.  The origin of the other symbols is
     currently unknown.  */
  return (name && (strcmp ("_sigreturn", name) == 0
		   || strcmp ("_sigacthandler", name) == 0
		   || strcmp ("sigvechandler", name) == 0));
}