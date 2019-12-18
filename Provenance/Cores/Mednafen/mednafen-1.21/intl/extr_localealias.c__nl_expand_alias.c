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
struct alias_map {char const* alias; char* value; } ;

/* Variables and functions */
 char* LOCALE_ALIAS_PATH ; 
 char const PATH_SEPARATOR ; 
 int /*<<< orphan*/  __libc_lock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __libc_lock_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ alias_compare ; 
 scalar_t__ bsearch (struct alias_map*,int /*<<< orphan*/ ,scalar_t__,int,int (*) (void const*,void const*)) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  map ; 
 scalar_t__ nmap ; 
 size_t read_alias_file (char const*,int) ; 

const char *
_nl_expand_alias (const char *name)
{
  static const char *locale_alias_path;
  struct alias_map *retval;
  const char *result = NULL;
  size_t added;

  __libc_lock_lock (lock);

  if (locale_alias_path == NULL)
    locale_alias_path = LOCALE_ALIAS_PATH;

  do
    {
      struct alias_map item;

      item.alias = name;

      if (nmap > 0)
	retval = (struct alias_map *) bsearch (&item, map, nmap,
					       sizeof (struct alias_map),
					       (int (*) (const void *,
							 const void *)
						) alias_compare);
      else
	retval = NULL;

      /* We really found an alias.  Return the value.  */
      if (retval != NULL)
	{
	  result = retval->value;
	  break;
	}

      /* Perhaps we can find another alias file.  */
      added = 0;
      while (added == 0 && locale_alias_path[0] != '\0')
	{
	  const char *start;

	  while (locale_alias_path[0] == PATH_SEPARATOR)
	    ++locale_alias_path;
	  start = locale_alias_path;

	  while (locale_alias_path[0] != '\0'
		 && locale_alias_path[0] != PATH_SEPARATOR)
	    ++locale_alias_path;

	  if (start < locale_alias_path)
	    added = read_alias_file (start, locale_alias_path - start);
	}
    }
  while (added != 0);

  __libc_lock_unlock (lock);

  return result;
}