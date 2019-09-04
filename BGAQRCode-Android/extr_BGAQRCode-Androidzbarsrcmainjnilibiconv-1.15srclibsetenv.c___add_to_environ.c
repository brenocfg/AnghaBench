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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LOCK ; 
 int /*<<< orphan*/  STORE_VALUE (char*) ; 
 int /*<<< orphan*/  UNLOCK ; 
 char** __environ ; 
 int /*<<< orphan*/  __set_errno (int /*<<< orphan*/ ) ; 
 char** last_environ ; 
 scalar_t__ malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 scalar_t__ realloc (char**,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t const) ; 

int
__add_to_environ (const char *name, const char *value, const char *combined,
                  int replace)
{
  char **ep;
  size_t size;
  const size_t namelen = strlen (name);
  const size_t vallen = value != NULL ? strlen (value) + 1 : 0;

  LOCK;

  /* We have to get the pointer now that we have the lock and not earlier
     since another thread might have created a new environment.  */
  ep = __environ;

  size = 0;
  if (ep != NULL)
    {
      for (; *ep != NULL; ++ep)
        if (!strncmp (*ep, name, namelen) && (*ep)[namelen] == '=')
          break;
        else
          ++size;
    }

  if (ep == NULL || *ep == NULL)
    {
      char **new_environ;
#ifdef USE_TSEARCH
      char *new_value;
#endif

      /* We allocated this space; we can extend it.  */
      new_environ =
        (char **) (last_environ == NULL
                   ? malloc ((size + 2) * sizeof (char *))
                   : realloc (last_environ, (size + 2) * sizeof (char *)));
      if (new_environ == NULL)
        {
          /* It's easier to set errno to ENOMEM than to rely on the
             'malloc-posix' and 'realloc-posix' gnulib modules.  */
          __set_errno (ENOMEM);
          UNLOCK;
          return -1;
        }

      /* If the whole entry is given add it.  */
      if (combined != NULL)
        /* We must not add the string to the search tree since it belongs
           to the user.  */
        new_environ[size] = (char *) combined;
      else
        {
          /* See whether the value is already known.  */
#ifdef USE_TSEARCH
# ifdef _LIBC
          new_value = (char *) alloca (namelen + 1 + vallen);
          __mempcpy (__mempcpy (__mempcpy (new_value, name, namelen), "=", 1),
                     value, vallen);
# else
          new_value = (char *) malloca (namelen + 1 + vallen);
          if (new_value == NULL)
            {
              __set_errno (ENOMEM);
              UNLOCK;
              return -1;
            }
          memcpy (new_value, name, namelen);
          new_value[namelen] = '=';
          memcpy (&new_value[namelen + 1], value, vallen);
# endif

          new_environ[size] = KNOWN_VALUE (new_value);
          if (new_environ[size] == NULL)
#endif
            {
              new_environ[size] = (char *) malloc (namelen + 1 + vallen);
              if (new_environ[size] == NULL)
                {
#if defined USE_TSEARCH && !defined _LIBC
                  freea (new_value);
#endif
                  __set_errno (ENOMEM);
                  UNLOCK;
                  return -1;
                }

#ifdef USE_TSEARCH
              memcpy (new_environ[size], new_value, namelen + 1 + vallen);
#else
              memcpy (new_environ[size], name, namelen);
              new_environ[size][namelen] = '=';
              memcpy (&new_environ[size][namelen + 1], value, vallen);
#endif
              /* And save the value now.  We cannot do this when we remove
                 the string since then we cannot decide whether it is a
                 user string or not.  */
              STORE_VALUE (new_environ[size]);
            }
#if defined USE_TSEARCH && !defined _LIBC
          freea (new_value);
#endif
        }

      if (__environ != last_environ)
        memcpy ((char *) new_environ, (char *) __environ,
                size * sizeof (char *));

      new_environ[size + 1] = NULL;

      last_environ = __environ = new_environ;
    }
  else if (replace)
    {
      char *np;

      /* Use the user string if given.  */
      if (combined != NULL)
        np = (char *) combined;
      else
        {
#ifdef USE_TSEARCH
          char *new_value;
# ifdef _LIBC
          new_value = alloca (namelen + 1 + vallen);
          __mempcpy (__mempcpy (__mempcpy (new_value, name, namelen), "=", 1),
                     value, vallen);
# else
          new_value = malloca (namelen + 1 + vallen);
          if (new_value == NULL)
            {
              __set_errno (ENOMEM);
              UNLOCK;
              return -1;
            }
          memcpy (new_value, name, namelen);
          new_value[namelen] = '=';
          memcpy (&new_value[namelen + 1], value, vallen);
# endif

          np = KNOWN_VALUE (new_value);
          if (np == NULL)
#endif
            {
              np = (char *) malloc (namelen + 1 + vallen);
              if (np == NULL)
                {
#if defined USE_TSEARCH && !defined _LIBC
                  freea (new_value);
#endif
                  __set_errno (ENOMEM);
                  UNLOCK;
                  return -1;
                }

#ifdef USE_TSEARCH
              memcpy (np, new_value, namelen + 1 + vallen);
#else
              memcpy (np, name, namelen);
              np[namelen] = '=';
              memcpy (&np[namelen + 1], value, vallen);
#endif
              /* And remember the value.  */
              STORE_VALUE (np);
            }
#if defined USE_TSEARCH && !defined _LIBC
          freea (new_value);
#endif
        }

      *ep = np;
    }

  UNLOCK;

  return 0;
}