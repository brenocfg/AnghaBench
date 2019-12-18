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
 char* getenv (char const*) ; 
 int /*<<< orphan*/  gomp_error (char*,char const*) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static void
parse_boolean (const char *name, bool *value)
{
  const char *env;

  env = getenv (name);
  if (env == NULL)
    return;

  while (isspace ((unsigned char) *env))
    ++env;
  if (strncasecmp (env, "true", 4) == 0)
    {
      *value = true;
      env += 4;
    }
  else if (strncasecmp (env, "false", 5) == 0)
    {
      *value = false;
      env += 5;
    }
  else
    env = "X";
  while (isspace ((unsigned char) *env))
    ++env;
  if (*env != '\0')
    gomp_error ("Invalid value for environment variable %s", name);
}