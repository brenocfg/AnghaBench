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
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  exit_failure ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  xalloc_fail_func () ; 
 int /*<<< orphan*/  xalloc_msg_memory_exhausted ; 

void
xalloc_die (void)
{
  if (xalloc_fail_func)
    (*xalloc_fail_func) ();
  error (exit_failure, 0, "%s", _(xalloc_msg_memory_exhausted));
  /* The `noreturn' cannot be given to error, since it may return if
     its first argument is 0.  To help compilers understand the
     xalloc_die does terminate, call abort.  */
  abort ();
}