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
 int /*<<< orphan*/  exec_file_command (char*,int) ; 
 int /*<<< orphan*/  file_changed_hook (char*) ; 
 int /*<<< orphan*/  symbol_file_command (char*,int) ; 

__attribute__((used)) static void
file_command (char *arg, int from_tty)
{
  /* FIXME, if we lose on reading the symbol file, we should revert
     the exec file, but that's rough.  */
  exec_file_command (arg, from_tty);
  symbol_file_command (arg, from_tty);
  if (file_changed_hook)
    file_changed_hook (arg);
}