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
 int /*<<< orphan*/  BINDIR ; 
 scalar_t__ CONST_STRNEQ (char*,char*) ; 
 char const* TARGET_SYSTEM_ROOT ; 
 int /*<<< orphan*/  TOOLBINDIR ; 
 char* get_relative_sysroot (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static const char *
get_sysroot (int argc, char **argv)
{
  int i;
  const char *path;

  for (i = 1; i < argc; i++)
    if (CONST_STRNEQ (argv[i], "--sysroot="))
      return argv[i] + strlen ("--sysroot=");

  path = get_relative_sysroot (BINDIR);
  if (path)
    return path;

  path = get_relative_sysroot (TOOLBINDIR);
  if (path)
    return path;

  return TARGET_SYSTEM_ROOT;
}