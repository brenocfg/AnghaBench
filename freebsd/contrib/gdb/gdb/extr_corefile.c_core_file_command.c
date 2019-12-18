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
struct target_ops {int /*<<< orphan*/  (* to_open ) (char*,int) ;int /*<<< orphan*/  (* to_detach ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 struct target_ops* find_core_target () ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  stub2 (char*,int) ; 

void
core_file_command (char *filename, int from_tty)
{
  struct target_ops *t;

  dont_repeat ();		/* Either way, seems bogus. */

  t = find_core_target ();
  if (t == NULL)
    error ("GDB can't read core files on this machine.");

  if (!filename)
    (t->to_detach) (filename, from_tty);
  else
    (t->to_open) (filename, from_tty);
}