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
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int STRLEN_CONST (char*) ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 char* filestream_getline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (char*,char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_absolute (char*) ; 
 int /*<<< orphan*/  path_is_valid (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

char *video_shader_read_reference_path(const char *path)
{
   /* We want shader presets that point to other presets.
    *
    * While config_file_new_from_path_to_string() does support the
    * #include directive, it will not rebase relative paths on
    * the include path.
    *
    * There's a plethora of reasons why a general solution is hard:
    *  - it's impossible to distinguish a generic string from a (relative) path
    *  - config_file_new_from_path_to_string() doesn't return the include path,
    *    so we cannot rebase afterwards
    *  - #include is recursive, so we'd actually need to track the include path
    *    for every setting
    *
    * So instead, we use a custom #reference directive, which is just a
    * one-time/non-recursive redirection, e.g.
    *
    * #reference "<path to config>"
    * or
    * #reference <path to config>
    *
    * which we will load as config_file_new_from_path_to_string(<path to config>).
    */
   char *reference     = NULL;
   RFILE *file         = NULL;
   char *line          = NULL;

   if (string_is_empty(path))
     goto end;
   if (!path_is_valid(path))
     goto end;

   file = filestream_open(path, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);

   if (!file)
     goto end;

   line = filestream_getline(file);
   filestream_close(file);

   if (line && !strncmp("#reference", line, STRLEN_CONST("#reference")))
   {
      char *ref_path = line + STRLEN_CONST("#reference");

      /* have at least 1 whitespace */
      if (!isspace(*ref_path))
         goto end;
      ref_path++;

      while (isspace(*ref_path))
         ref_path++;

      if (*ref_path == '\"')
      {
         /* remove "" */
         char *p;
         ref_path++;

         p = ref_path;
         while (*p != '\0' && *p != '\"')
            p++;

         if (*p == '\"')
         {
            *p = '\0';
         }
         else
         {
            /* if there's no second ", remove whitespace at the end */
            p--;
            while (isspace(*p))
               *p-- = '\0';
         }
      }
      else
      {
         /* remove whitespace at the end (e.g. carriage return) */
         char *end = ref_path + strlen(ref_path) - 1;
         while (isspace(*end))
            *end-- = '\0';
      }

      if (string_is_empty(ref_path))
         goto end;

      reference = (char *)malloc(PATH_MAX_LENGTH);

      if (!reference)
         goto end;

      /* rebase relative reference path */
      if (!path_is_absolute(ref_path))
      {
         fill_pathname_resolve_relative(reference,
               path, ref_path, PATH_MAX_LENGTH);
      }
      else
         strlcpy(reference, ref_path, PATH_MAX_LENGTH);
   }

end:
   if (line)
      free(line);

   return reference;
}