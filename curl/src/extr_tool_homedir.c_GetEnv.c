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
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf1 ;
typedef  int DWORD ;

/* Variables and functions */
 int ExpandEnvironmentStringsA (char const*,char*,int) ; 
 int GetEnvironmentVariableA (char const*,char*,int) ; 
 char* getenv (char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *GetEnv(const char *variable, char do_expand)
{
  char *env = NULL;
#ifdef WIN32
  char  buf1[1024], buf2[1024];
  DWORD rc;

  /* Don't use getenv(); it doesn't find variable added after program was
   * started. Don't accept truncated results (i.e. rc >= sizeof(buf1)).  */

  rc = GetEnvironmentVariableA(variable, buf1, sizeof(buf1));
  if(rc > 0 && rc < sizeof(buf1)) {
    env = buf1;
    variable = buf1;
  }
  if(do_expand && strchr(variable, '%')) {
    /* buf2 == variable if not expanded */
    rc = ExpandEnvironmentStringsA(variable, buf2, sizeof(buf2));
    if(rc > 0 && rc < sizeof(buf2) &&
       !strchr(buf2, '%'))    /* no vars still unexpanded */
      env = buf2;
  }
#else
  (void)do_expand;
  /* no length control */
  env = getenv(variable);
#endif
  return (env && env[0]) ? strdup(env) : NULL;
}