#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hProcess; int /*<<< orphan*/  hThread; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPSTARTUPINFO ;
typedef  TYPE_1__* LPPROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcess (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 char** alloca (int) ; 
 char* argv_to_cmdline (char* const*) ; 
 int /*<<< orphan*/  env_compare ; 
 char* find_executable (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char**,char* const*,int) ; 
 int /*<<< orphan*/  qsort (char**,int,int,int /*<<< orphan*/ ) ; 
 char* stpcpy (char*,char*) ; 
 scalar_t__ strlen (char* const) ; 

__attribute__((used)) static long
win32_spawn (const char *executable,
	     BOOL search,
	     char *const *argv,
             char *const *env, /* array of strings of the form: VAR=VALUE */
	     DWORD dwCreationFlags,
	     LPSTARTUPINFO si,
	     LPPROCESS_INFORMATION pi)
{
  char *full_executable;
  char *cmdline;
  char **env_copy;
  char *env_block = NULL;

  full_executable = NULL;
  cmdline = NULL;

  if (env)
    {
      int env_size;

      /* Count the number of environment bindings supplied.  */
      for (env_size = 0; env[env_size]; env_size++)
        continue;
    
      /* Assemble an environment block, if required.  This consists of
         VAR=VALUE strings juxtaposed (with one null character between each
         pair) and an additional null at the end.  */
      if (env_size > 0)
        {
          int var;
          int total_size = 1; /* 1 is for the final null.  */
          char *bufptr;
    
          /* Windows needs the members of the block to be sorted by variable
             name.  */
          env_copy = alloca (sizeof (char *) * env_size);
          memcpy (env_copy, env, sizeof (char *) * env_size);
          qsort (env_copy, env_size, sizeof (char *), env_compare);
    
          for (var = 0; var < env_size; var++)
            total_size += strlen (env[var]) + 1;
    
          env_block = malloc (total_size);
          bufptr = env_block;
          for (var = 0; var < env_size; var++)
            bufptr = stpcpy (bufptr, env_copy[var]) + 1;
    
          *bufptr = '\0';
        }
    }

  full_executable = find_executable (executable, search);
  if (!full_executable)
    goto error;
  cmdline = argv_to_cmdline (argv);
  if (!cmdline)
    goto error;
    
  /* Create the child process.  */  
  if (!CreateProcess (full_executable, cmdline, 
		      /*lpProcessAttributes=*/NULL,
		      /*lpThreadAttributes=*/NULL,
		      /*bInheritHandles=*/TRUE,
		      dwCreationFlags,
		      (LPVOID) env_block,
		      /*lpCurrentDirectory=*/NULL,
		      si,
		      pi))
    {
      if (env_block)
        free (env_block);

      free (full_executable);

      return -1;
    }

  /* Clean up.  */
  CloseHandle (pi->hThread);
  free (full_executable);
  if (env_block)
    free (env_block);

  return (long) pi->hProcess;

 error:
  if (env_block)
    free (env_block);
  if (cmdline)
    free (cmdline);
  if (full_executable)
    free (full_executable);

  return -1;
}