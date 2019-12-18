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
 int /*<<< orphan*/  dont_repeat () ; 
 char* get_in_environ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_environ ; 
 int /*<<< orphan*/  mod_path (char*,char**) ; 
 int /*<<< orphan*/  path_info (char*,int) ; 
 int /*<<< orphan*/  path_var_name ; 
 int /*<<< orphan*/  set_in_environ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
path_command (char *dirname, int from_tty)
{
  char *exec_path;
  char *env;
  dont_repeat ();
  env = get_in_environ (inferior_environ, path_var_name);
  /* Can be null if path is not set */
  if (!env)
    env = "";
  exec_path = xstrdup (env);
  mod_path (dirname, &exec_path);
  set_in_environ (inferior_environ, path_var_name, exec_path);
  xfree (exec_path);
  if (from_tty)
    path_info ((char *) NULL, from_tty);
}