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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xexit (int) ; 

void
ld_abort (const char *file, int line, const char *fn)
{
  if (fn != NULL)
    einfo (_("%P: internal error: aborting at %s line %d in %s\n"),
	   file, line, fn);
  else
    einfo (_("%P: internal error: aborting at %s line %d\n"),
	   file, line);
  einfo (_("%P%F: please report this bug\n"));
  xexit (1);
}