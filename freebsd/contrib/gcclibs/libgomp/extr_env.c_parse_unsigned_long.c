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
 scalar_t__ errno ; 
 char* getenv (char const*) ; 
 int /*<<< orphan*/  gomp_error (char*,char const*) ; 
 scalar_t__ isspace (unsigned char) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static bool
parse_unsigned_long (const char *name, unsigned long *pvalue)
{
  char *env, *end;
  unsigned long value;

  env = getenv (name);
  if (env == NULL)
    return false;

  while (isspace ((unsigned char) *env))
    ++env;
  if (*env == '\0')
    goto invalid;

  errno = 0;
  value = strtoul (env, &end, 10);
  if (errno || (long) value <= 0)
    goto invalid;

  while (isspace ((unsigned char) *end))
    ++end;
  if (*end != '\0')
    goto invalid;

  *pvalue = value;
  return true;

 invalid:
  gomp_error ("Invalid value for environment variable %s", name);
  return false;
}