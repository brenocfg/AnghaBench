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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc_exit_failure ; 

void
xalloc_die ()
{
  error (xmalloc_exit_failure, 0, _("memory exhausted"));
  /* _Noreturn cannot be given to error, since it may return if
     its first argument is 0.  To help compilers understand the
     xalloc_die does terminate, call exit. */
  exit (EXIT_FAILURE);
}