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
 int /*<<< orphan*/  GFS_DYNAMIC ; 
 int /*<<< orphan*/  GFS_GUIDED ; 
 int /*<<< orphan*/  GFS_STATIC ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  gomp_error (char*) ; 
 unsigned long gomp_run_sched_chunk ; 
 int /*<<< orphan*/  gomp_run_sched_var ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static void
parse_schedule (void)
{
  char *env, *end;
  unsigned long value;

  env = getenv ("OMP_SCHEDULE");
  if (env == NULL)
    return;

  while (isspace ((unsigned char) *env))
    ++env;
  if (strncasecmp (env, "static", 6) == 0)
    {
      gomp_run_sched_var = GFS_STATIC;
      env += 6;
    }
  else if (strncasecmp (env, "dynamic", 7) == 0)
    {
      gomp_run_sched_var = GFS_DYNAMIC;
      env += 7;
    }
  else if (strncasecmp (env, "guided", 6) == 0)
    {
      gomp_run_sched_var = GFS_GUIDED;
      env += 6;
    }
  else
    goto unknown;

  while (isspace ((unsigned char) *env))
    ++env;
  if (*env == '\0')
    return;
  if (*env++ != ',')
    goto unknown;
  while (isspace ((unsigned char) *env))
    ++env;
  if (*env == '\0')
    goto invalid;

  errno = 0;
  value = strtoul (env, &end, 10);
  if (errno)
    goto invalid;

  while (isspace ((unsigned char) *end))
    ++end;
  if (*end != '\0')
    goto invalid;

  gomp_run_sched_chunk = value;
  return;

 unknown:
  gomp_error ("Unknown value for environment variable OMP_SCHEDULE");
  return;

 invalid:
  gomp_error ("Invalid value for chunk size in "
	      "environment variable OMP_SCHEDULE");
  return;
}