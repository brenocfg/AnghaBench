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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  size_t ssize_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 scalar_t__ DOUBLE_SLASH_IS_DISTINCT_ROOT ; 
 int EINVAL ; 
 int ELOOP ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTDIR ; 
 size_t FILE_SYSTEM_PREFIX_LEN (char const*) ; 
 scalar_t__ ISSLASH (char const) ; 
 scalar_t__ IS_ABSOLUTE_FILE_NAME (char const*) ; 
 int MAXSYMLINKS ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PC_PATH_MAX ; 
 int /*<<< orphan*/  __getcwd (char*,long) ; 
 size_t __readlink (char*,char*,long) ; 
 int /*<<< orphan*/  __set_errno (int) ; 
 int /*<<< orphan*/  alloc_failed () ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freea (char*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* malloc (long) ; 
 char* malloca (long) ; 
 char* memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 long pathconf (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 

char *
__realpath (const char *name, char *resolved)
{
  char *rpath, *dest, *extra_buf = NULL;
  const char *start, *end, *rpath_limit;
  long int path_max;
  int num_links = 0;
  size_t prefix_len;

  if (name == NULL)
    {
      /* As per Single Unix Specification V2 we must return an error if
         either parameter is a null pointer.  We extend this to allow
         the RESOLVED parameter to be NULL in case the we are expected to
         allocate the room for the return value.  */
      __set_errno (EINVAL);
      return NULL;
    }

  if (name[0] == '\0')
    {
      /* As per Single Unix Specification V2 we must return an error if
         the name argument points to an empty string.  */
      __set_errno (ENOENT);
      return NULL;
    }

#ifdef PATH_MAX
  path_max = PATH_MAX;
#else
  path_max = pathconf (name, _PC_PATH_MAX);
  if (path_max <= 0)
    path_max = 8192;
#endif

  if (resolved == NULL)
    {
      rpath = malloc (path_max);
      if (rpath == NULL)
        {
          alloc_failed ();
          return NULL;
        }
    }
  else
    rpath = resolved;
  rpath_limit = rpath + path_max;

  /* This is always zero for Posix hosts, but can be 2 for MS-Windows
     and MS-DOS X:/foo/bar file names.  */
  prefix_len = FILE_SYSTEM_PREFIX_LEN (name);

  if (!IS_ABSOLUTE_FILE_NAME (name))
    {
      if (!__getcwd (rpath, path_max))
        {
          rpath[0] = '\0';
          goto error;
        }
      dest = strchr (rpath, '\0');
      start = name;
      prefix_len = FILE_SYSTEM_PREFIX_LEN (rpath);
    }
  else
    {
      dest = rpath;
      if (prefix_len)
        {
          memcpy (rpath, name, prefix_len);
          dest += prefix_len;
        }
      *dest++ = '/';
      if (DOUBLE_SLASH_IS_DISTINCT_ROOT)
        {
          if (ISSLASH (name[1]) && !ISSLASH (name[2]) && !prefix_len)
            *dest++ = '/';
          *dest = '\0';
        }
      start = name + prefix_len;
    }

  for (end = start; *start; start = end)
    {
#ifdef _LIBC
      struct stat64 st;
#else
      struct stat st;
#endif

      /* Skip sequence of multiple path-separators.  */
      while (ISSLASH (*start))
        ++start;

      /* Find end of path component.  */
      for (end = start; *end && !ISSLASH (*end); ++end)
        /* Nothing.  */;

      if (end - start == 0)
        break;
      else if (end - start == 1 && start[0] == '.')
        /* nothing */;
      else if (end - start == 2 && start[0] == '.' && start[1] == '.')
        {
          /* Back up to previous component, ignore if at root already.  */
          if (dest > rpath + prefix_len + 1)
            for (--dest; dest > rpath && !ISSLASH (dest[-1]); --dest)
              continue;
          if (DOUBLE_SLASH_IS_DISTINCT_ROOT
              && dest == rpath + 1 && !prefix_len
              && ISSLASH (*dest) && !ISSLASH (dest[1]))
            dest++;
        }
      else
        {
          size_t new_size;

          if (!ISSLASH (dest[-1]))
            *dest++ = '/';

          if (dest + (end - start) >= rpath_limit)
            {
              ptrdiff_t dest_offset = dest - rpath;
              char *new_rpath;

              if (resolved)
                {
                  __set_errno (ENAMETOOLONG);
                  if (dest > rpath + prefix_len + 1)
                    dest--;
                  *dest = '\0';
                  goto error;
                }
              new_size = rpath_limit - rpath;
              if (end - start + 1 > path_max)
                new_size += end - start + 1;
              else
                new_size += path_max;
              new_rpath = (char *) realloc (rpath, new_size);
              if (new_rpath == NULL)
                {
                  alloc_failed ();
                  goto error;
                }
              rpath = new_rpath;
              rpath_limit = rpath + new_size;

              dest = rpath + dest_offset;
            }

#ifdef _LIBC
          dest = __mempcpy (dest, start, end - start);
#else
          memcpy (dest, start, end - start);
          dest += end - start;
#endif
          *dest = '\0';

#ifdef _LIBC
          if (__lxstat64 (_STAT_VER, rpath, &st) < 0)
#else
          if (lstat (rpath, &st) < 0)
#endif
            goto error;

          if (S_ISLNK (st.st_mode))
            {
              char *buf;
              size_t len;
              ssize_t n;

              if (++num_links > MAXSYMLINKS)
                {
                  __set_errno (ELOOP);
                  goto error;
                }

              buf = malloca (path_max);
              if (!buf)
                {
                  __set_errno (ENOMEM);
                  goto error;
                }

              n = __readlink (rpath, buf, path_max - 1);
              if (n < 0)
                {
                  int saved_errno = errno;
                  freea (buf);
                  __set_errno (saved_errno);
                  goto error;
                }
              buf[n] = '\0';

              if (!extra_buf)
                {
                  extra_buf = malloca (path_max);
                  if (!extra_buf)
                    {
                      freea (buf);
                      __set_errno (ENOMEM);
                      goto error;
                    }
                }

              len = strlen (end);
              /* Check that n + len + 1 doesn't overflow and is <= path_max. */
              if (n >= SIZE_MAX - len || n + len >= path_max)
                {
                  freea (buf);
                  __set_errno (ENAMETOOLONG);
                  goto error;
                }

              /* Careful here, end may be a pointer into extra_buf... */
              memmove (&extra_buf[n], end, len + 1);
              name = end = memcpy (extra_buf, buf, n);

              if (IS_ABSOLUTE_FILE_NAME (buf))
                {
                  size_t pfxlen = FILE_SYSTEM_PREFIX_LEN (buf);

                  if (pfxlen)
                    memcpy (rpath, buf, pfxlen);
                  dest = rpath + pfxlen;
                  *dest++ = '/'; /* It's an absolute symlink */
                  if (DOUBLE_SLASH_IS_DISTINCT_ROOT)
                    {
                      if (ISSLASH (buf[1]) && !ISSLASH (buf[2]) && !pfxlen)
                        *dest++ = '/';
                      *dest = '\0';
                    }
                  /* Install the new prefix to be in effect hereafter.  */
                  prefix_len = pfxlen;
                }
              else
                {
                  /* Back up to previous component, ignore if at root
                     already: */
                  if (dest > rpath + prefix_len + 1)
                    for (--dest; dest > rpath && !ISSLASH (dest[-1]); --dest)
                      continue;
                  if (DOUBLE_SLASH_IS_DISTINCT_ROOT && dest == rpath + 1
                      && ISSLASH (*dest) && !ISSLASH (dest[1]) && !prefix_len)
                    dest++;
                }
            }
          else if (!S_ISDIR (st.st_mode) && *end != '\0')
            {
              __set_errno (ENOTDIR);
              goto error;
            }
        }
    }
  if (dest > rpath + prefix_len + 1 && ISSLASH (dest[-1]))
    --dest;
  if (DOUBLE_SLASH_IS_DISTINCT_ROOT && dest == rpath + 1 && !prefix_len
      && ISSLASH (*dest) && !ISSLASH (dest[1]))
    dest++;
  *dest = '\0';

  if (extra_buf)
    freea (extra_buf);

  return rpath;

error:
  {
    int saved_errno = errno;
    if (extra_buf)
      freea (extra_buf);
    if (resolved == NULL)
      free (rpath);
    __set_errno (saved_errno);
  }
  return NULL;
}