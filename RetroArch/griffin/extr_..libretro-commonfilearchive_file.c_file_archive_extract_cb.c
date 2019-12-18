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
typedef  int /*<<< orphan*/  wanted_file ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct archive_extract_userdata {char const* archive_path; int found_file; int /*<<< orphan*/  extracted_file_path; int /*<<< orphan*/  first_extracted_file_path; int /*<<< orphan*/  extraction_directory; int /*<<< orphan*/  ext; } ;
typedef  int /*<<< orphan*/  new_path ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 scalar_t__ file_archive_perform_mode (char*,char const*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct archive_extract_userdata*) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fill_pathname_resolve_relative (char*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path_basename (char const*) ; 
 char* path_get_archive_delim (char const*) ; 
 char* path_get_extension (char const*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_equal_noncase (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ string_list_find_elem (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int file_archive_extract_cb(const char *name, const char *valid_exts,
      const uint8_t *cdata,
      unsigned cmode, uint32_t csize, uint32_t size,
      uint32_t checksum, struct archive_extract_userdata *userdata)
{
   const char *ext                   = path_get_extension(name);

   /* Extract first file that matches our list. */
   if (ext && string_list_find_elem(userdata->ext, ext))
   {
      char new_path[PATH_MAX_LENGTH];
      char wanted_file[PATH_MAX_LENGTH];
      const char *delim                 = NULL;

      new_path[0] = wanted_file[0]      = '\0';

      if (userdata->extraction_directory)
         fill_pathname_join(new_path, userdata->extraction_directory,
               path_basename(name), sizeof(new_path));
      else
         fill_pathname_resolve_relative(new_path, userdata->archive_path,
               path_basename(name), sizeof(new_path));

      userdata->first_extracted_file_path = strdup(new_path);

      delim = path_get_archive_delim(userdata->archive_path);

      if (delim)
      {
         strlcpy(wanted_file, delim + 1, sizeof(wanted_file));

         if (!string_is_equal_noncase(userdata->extracted_file_path,
                   wanted_file))
           return 1; /* keep searching for the right file */
      }
      else
         strlcpy(wanted_file, userdata->archive_path, sizeof(wanted_file));

      if (file_archive_perform_mode(new_path,
                valid_exts, cdata, cmode, csize, size,
                0, userdata))
         userdata->found_file = true;

      return 0;
   }

   return 1;
}