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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  LPSTARTUPINFO ;
typedef  int /*<<< orphan*/  LPPROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _O_RDONLY ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char const*,int /*<<< orphan*/ ) ; 
 int _read (int,char*,int) ; 
 int /*<<< orphan*/  backslashify (char*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mingw_rootify (char*) ; 
 char* msys_rootify (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int win32_spawn (char const*,int /*<<< orphan*/ ,char* const*,char* const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
spawn_script (const char *executable, char *const *argv,
              char* const *env,
	      DWORD dwCreationFlags,
	      LPSTARTUPINFO si,
	      LPPROCESS_INFORMATION pi)
{
  int pid = -1;
  int save_errno = errno;
  int fd = _open (executable, _O_RDONLY);

  if (fd >= 0)
    {
      char buf[MAX_PATH + 5];
      int len = _read (fd, buf, sizeof (buf) - 1);
      _close (fd);
      if (len > 3)
	{
	  char *eol;
	  buf[len] = '\0';
	  eol = strchr (buf, '\n');
	  if (eol && strncmp (buf, "#!", 2) == 0)
	    {
	      char *executable1;
	      const char ** avhere = (const char **) --argv;
	      do
		*eol = '\0';
	      while (*--eol == '\r' || *eol == ' ' || *eol == '\t');
	      for (executable1 = buf + 2; *executable1 == ' ' || *executable1 == '\t'; executable1++)
		continue;

	      backslashify (executable1);
	      *avhere = executable1;
#ifndef USE_MINGW_MSYS
	      executable = strrchr (executable1, '\\') + 1;
	      if (!executable)
		executable = executable1;
	      pid = win32_spawn (executable, TRUE, argv, env,
				 dwCreationFlags, si, pi);
#else
	      if (strchr (executable1, '\\') == NULL)
		pid = win32_spawn (executable1, TRUE, argv, env,
				   dwCreationFlags, si, pi);
	      else if (executable1[0] != '\\')
		pid = win32_spawn (executable1, FALSE, argv, env,
				   dwCreationFlags, si, pi);
	      else
		{
		  const char *newex = mingw_rootify (executable1);
		  *avhere = newex;
		  pid = win32_spawn (newex, FALSE, argv, env,
				     dwCreationFlags, si, pi);
		  if (executable1 != newex)
		    free ((char *) newex);
		  if (pid < 0)
		    {
		      newex = msys_rootify (executable1);
		      if (newex != executable1)
			{
			  *avhere = newex;
			  pid = win32_spawn (newex, FALSE, argv, env,
					     dwCreationFlags, si, pi);
			  free ((char *) newex);
			}
		    }
		}
#endif
	    }
	}
    }
  if (pid < 0)
    errno = save_errno;
  return pid;
}