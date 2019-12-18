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
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_application_dir (char*,int) ; 
 int /*<<< orphan*/  fill_pathname_home_dir (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  path_char_is_slash (char) ; 
 char const* path_default_slash () ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 size_t strlcpy (char*,char const*,size_t) ; 

void fill_pathname_expand_special(char *out_path,
      const char *in_path, size_t size)
{
#if !defined(RARCH_CONSOLE) && defined(RARCH_INTERNAL)
   if (in_path[0] == '~')
   {
      char *home_dir = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      home_dir[0] = '\0';

      fill_pathname_home_dir(home_dir,
         PATH_MAX_LENGTH * sizeof(char));

      if (*home_dir)
      {
         size_t src_size = strlcpy(out_path, home_dir, size);
         retro_assert(src_size < size);

         out_path  += src_size;
         size      -= src_size;

         if (!path_char_is_slash(out_path[-1]))
         {
            src_size = strlcpy(out_path, path_default_slash(), size);
            retro_assert(src_size < size);

            out_path += src_size;
            size -= src_size;
         }

         in_path += 2;
      }

      free(home_dir);
   }
   else if (in_path[0] == ':')
   {
      char *application_dir = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      application_dir[0]    = '\0';

      fill_pathname_application_dir(application_dir,
            PATH_MAX_LENGTH * sizeof(char));

      if (*application_dir)
      {
         size_t src_size   = strlcpy(out_path, application_dir, size);
         retro_assert(src_size < size);

         out_path  += src_size;
         size      -= src_size;

         if (!path_char_is_slash(out_path[-1]))
         {
            src_size = strlcpy(out_path, path_default_slash(), size);
            retro_assert(src_size < size);

            out_path += src_size;
            size     -= src_size;
         }

         in_path += 2;
      }

      free(application_dir);
   }
#endif

   retro_assert(strlcpy(out_path, in_path, size) < size);
}