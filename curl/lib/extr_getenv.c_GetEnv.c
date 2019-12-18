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
typedef  int /*<<< orphan*/  env ;

/* Variables and functions */
 int /*<<< orphan*/  ExpandEnvironmentStringsA (char*,char*,int) ; 
 char* getenv (char const*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static
char *GetEnv(const char *variable)
{
#if defined(_WIN32_WCE) || defined(CURL_WINDOWS_APP)
  (void)variable;
  return NULL;
#else
#ifdef WIN32
  char env[4096];
  char *temp = getenv(variable);
  env[0] = '\0';
  if(temp != NULL)
    ExpandEnvironmentStringsA(temp, env, sizeof(env));
  return (env[0] != '\0')?strdup(env):NULL;
#else
  char *env = getenv(variable);
  return (env && env[0])?strdup(env):NULL;
#endif
#endif
}