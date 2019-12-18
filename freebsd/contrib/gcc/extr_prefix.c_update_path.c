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
 int /*<<< orphan*/  ALWAYS_STRIP_DOTDOT ; 
 char DIR_SEPARATOR ; 
 char DIR_SEPARATOR_2 ; 
 scalar_t__ IS_DIR_SEPARATOR (char const) ; 
 int /*<<< orphan*/  UPDATE_PATH_HOST_CANONICALIZE (char*) ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 void* concat (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  std_prefix ; 
 char* strchr (char*,char) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  tr (char*,char,char) ; 
 char* translate_name (char*) ; 
 char* xstrdup (char const*) ; 

char *
update_path (const char *path, const char *key)
{
  char *result, *p;
  const int len = strlen (std_prefix);

  if (! strncmp (path, std_prefix, len)
      && (IS_DIR_SEPARATOR(path[len])
          || path[len] == '\0')
      && key != 0)
    {
      bool free_key = false;

      if (key[0] != '$')
	{
	  key = concat ("@", key, NULL);
	  free_key = true;
	}

      result = concat (key, &path[len], NULL);
      if (free_key)
	free ((char *) key);
      result = translate_name (result);
    }
  else
    result = xstrdup (path);

#ifndef ALWAYS_STRIP_DOTDOT
#define ALWAYS_STRIP_DOTDOT 0
#endif

  p = result;
  while (1)
    {
      char *src, *dest;

      p = strchr (p, '.');
      if (p == NULL)
	break;
      /* Look for `/../'  */
      if (p[1] == '.'
	  && IS_DIR_SEPARATOR (p[2])
	  && (p != result && IS_DIR_SEPARATOR (p[-1])))
	{
	  *p = 0;
	  if (!ALWAYS_STRIP_DOTDOT && access (result, X_OK) == 0)
	    {
	      *p = '.';
	      break;
	    }
	  else
	    {
	      /* We can't access the dir, so we won't be able to
		 access dir/.. either.  Strip out `dir/../'.  If `dir'
		 turns out to be `.', strip one more path component.  */
	      dest = p;
	      do
		{
		  --dest;
		  while (dest != result && IS_DIR_SEPARATOR (*dest))
		    --dest;
		  while (dest != result && !IS_DIR_SEPARATOR (dest[-1]))
		    --dest;
		}
	      while (dest != result && *dest == '.');
	      /* If we have something like `./..' or `/..', don't
		 strip anything more.  */
	      if (*dest == '.' || IS_DIR_SEPARATOR (*dest))
		{
		  *p = '.';
		  break;
		}
	      src = p + 3;
	      while (IS_DIR_SEPARATOR (*src))
		++src;
	      p = dest;
	      while ((*dest++ = *src++) != 0)
		;
	    }
	}
      else
	++p;
    }

#ifdef UPDATE_PATH_HOST_CANONICALIZE
  /* Perform host dependent canonicalization when needed.  */
  UPDATE_PATH_HOST_CANONICALIZE (result);
#endif

#ifdef DIR_SEPARATOR_2
  /* Convert DIR_SEPARATOR_2 to DIR_SEPARATOR.  */
  if (DIR_SEPARATOR_2 != DIR_SEPARATOR)
    tr (result, DIR_SEPARATOR_2, DIR_SEPARATOR);
#endif

#if defined (DIR_SEPARATOR) && !defined (DIR_SEPARATOR_2)
  if (DIR_SEPARATOR != '/')
    tr (result, '/', DIR_SEPARATOR);
#endif

  return result;
}