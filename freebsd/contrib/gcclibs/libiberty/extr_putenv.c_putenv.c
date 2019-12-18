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
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int setenv (char*,char const* const,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  unsetenv (char const*) ; 

int
putenv (const char *string)
{
  const char *const name_end = strchr (string, '=');

  if (name_end)
    {
      char *name = (char *) alloca (name_end - string + 1);
      memcpy (name, string, name_end - string);
      name[name_end - string] = '\0';
      return setenv (name, name_end + 1, 1);
    }

  unsetenv (string);
  return 0;
}