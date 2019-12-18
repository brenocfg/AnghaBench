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
 char* get_in_environ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_environ ; 
 int /*<<< orphan*/  path_var_name ; 
 int /*<<< orphan*/  puts_filtered (char*) ; 

__attribute__((used)) static void
path_info (char *args, int from_tty)
{
  puts_filtered ("Executable and object file path: ");
  puts_filtered (get_in_environ (inferior_environ, path_var_name));
  puts_filtered ("\n");
}