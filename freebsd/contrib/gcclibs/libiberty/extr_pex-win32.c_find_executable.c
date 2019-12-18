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
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char** no_suffixes ; 
 char** std_suffixes ; 
 int /*<<< orphan*/  strcat (char*,char const* const) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static char *
find_executable (const char *program, BOOL search)
{
  char *full_executable;
  char *e;
  size_t fe_len;
  const char *path = 0;
  const char *const *ext;
  const char *p, *q;
  size_t proglen = strlen (program);
  int has_extension = !!strchr (program, '.');
  int has_slash = (strchr (program, '/') || strchr (program, '\\'));
  HANDLE h;

  if (has_slash)
    search = FALSE;

  if (search)
    path = getenv ("PATH");
  if (!path)
    path = "";

  fe_len = 0;
  for (p = path; *p; p = q)
    {
      q = p;
      while (*q != ';' && *q != '\0')
	q++;
      if ((size_t)(q - p) > fe_len)
	fe_len = q - p;
      if (*q == ';')
	q++;
    }
  fe_len = fe_len + 1 + proglen + (has_extension ? 1 : 5);
  full_executable = xmalloc (fe_len);

  p = path;
  do
    {
      q = p;
      while (*q != ';' && *q != '\0')
	q++;

      e = full_executable;
      memcpy (e, p, q - p);
      e += (q - p);
      if (q - p)
	*e++ = '\\';
      strcpy (e, program);

      if (*q == ';')
	q++;

      for (e = full_executable; *e; e++)
	if (*e == '/')
	  *e = '\\';

      /* At this point, e points to the terminating NUL character for
         full_executable.  */
      for (ext = has_extension ? no_suffixes : std_suffixes; *ext; ext++)
	{
	  /* Remove any current extension.  */
	  *e = '\0';
	  /* Add the new one.  */
	  strcat (full_executable, *ext);

	  /* Attempt to open this file.  */
	  h = CreateFile (full_executable, GENERIC_READ,
			  FILE_SHARE_READ | FILE_SHARE_WRITE,
			  0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	  if (h != INVALID_HANDLE_VALUE)
	    goto found;
	}
      p = q;
    }
  while (*p);
  free (full_executable);
  return 0;

 found:
  CloseHandle (h);
  return full_executable;
}