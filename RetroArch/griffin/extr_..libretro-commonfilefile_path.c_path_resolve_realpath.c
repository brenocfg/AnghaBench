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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  _fullpath (char*,char*,size_t) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  path_is_absolute (char*) ; 
 int /*<<< orphan*/  realpath (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 size_t strlen (char*) ; 

char *path_resolve_realpath(char *buf, size_t size, bool resolve_symlinks)
{
#if !defined(RARCH_CONSOLE) && defined(RARCH_INTERNAL)
   char tmp[PATH_MAX_LENGTH];
#ifdef _WIN32
   strlcpy(tmp, buf, sizeof(tmp));
   if (!_fullpath(buf, tmp, size))
   {
      strlcpy(buf, tmp, size);
      return NULL;
   }
   return buf;
#else
   size_t t;
   char *p;
   const char *next;
   const char *buf_end;

   if (resolve_symlinks)
   {
      strlcpy(tmp, buf, sizeof(tmp));

      /* NOTE: realpath() expects at least PATH_MAX_LENGTH bytes in buf.
       * Technically, PATH_MAX_LENGTH needn't be defined, but we rely on it anyways.
       * POSIX 2008 can automatically allocate for you,
       * but don't rely on that. */
      if (!realpath(tmp, buf))
      {
         strlcpy(buf, tmp, size);
         return NULL;
      }

      return buf;
   }

   t = 0; /* length of output */
   buf_end = buf + strlen(buf);

   if (!path_is_absolute(buf))
   {
      size_t len;
      /* rebase on working directory */
      if (!getcwd(tmp, PATH_MAX_LENGTH-1))
         return NULL;

      len = strlen(tmp);
      t += len;

      if (tmp[len-1] != '/')
         tmp[t++] = '/';

      if (string_is_empty(buf))
         goto end;

      p = buf;
   }
   else
   {
      /* UNIX paths can start with multiple '/', copy those */
      for (p = buf; *p == '/'; p++)
         tmp[t++] = '/';
   }

   /* p points to just after a slash while 'next' points to the next slash
    * if there are no slashes, they point relative to where one would be */
   do
   {
      next = strchr(p, '/');
      if (!next)
         next = buf_end;

      if ((next - p == 2 && p[0] == '.' && p[1] == '.'))
      {
         p += 3;

         /* fail for illegal /.., //.. etc */
         if (t == 1 || tmp[t-2] == '/')
            return NULL;

         /* delete previous segment in tmp by adjusting size t
          * tmp[t-1] == '/', find '/' before that */
         t = t-2;
         while (tmp[t] != '/')
            t--;
         t++;
      }
      else if (next - p == 1 && p[0] == '.')
         p += 2;
      else if (next - p == 0)
         p += 1;
      else
      {
         /* fail when truncating */
         if (t + next-p+1 > PATH_MAX_LENGTH-1)
            return NULL;

         while (p <= next)
            tmp[t++] = *p++;
      }

   }
   while (next < buf_end);

end:
   tmp[t] = '\0';
   strlcpy(buf, tmp, size);
   return buf;
#endif
#endif
   return NULL;
}