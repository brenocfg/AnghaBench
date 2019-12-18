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
typedef  char wchar_t ;

/* Variables and functions */
 scalar_t__ _wrename (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ rename (char const*,char const*) ; 
 char* utf8_to_local_string_alloc (char const*) ; 
 char* utf8_to_utf16_string_alloc (char const*) ; 

int retro_vfs_file_rename_impl(const char *old_path, const char *new_path)
{
#if defined(_WIN32) && !defined(_XBOX)
   /* Win32 (no Xbox) */
   int ret                 = -1;
#if defined(_WIN32_WINNT) && _WIN32_WINNT < 0x0500
   char *old_path_local    = NULL;
#else
   wchar_t *old_path_wide  = NULL;
#endif

   if (!old_path || !*old_path || !new_path || !*new_path)
      return -1;

#if defined(_WIN32_WINNT) && _WIN32_WINNT < 0x0500
   old_path_local = utf8_to_local_string_alloc(old_path);

   if (old_path_local)
   {
      char *new_path_local = utf8_to_local_string_alloc(new_path);

      if (new_path_local)
      {
         if (rename(old_path_local, new_path_local) == 0)
            ret = 0;
         free(new_path_local);
      }

      free(old_path_local);
   }
#else
   old_path_wide = utf8_to_utf16_string_alloc(old_path);

   if (old_path_wide)
   {
      wchar_t *new_path_wide = utf8_to_utf16_string_alloc(new_path);

      if (new_path_wide)
      {
         if (_wrename(old_path_wide, new_path_wide) == 0)
            ret = 0;
         free(new_path_wide);
      }

      free(old_path_wide);
   }
#endif
   return ret;

#elif defined(ORBIS)
   /* Orbis */
   /* TODO/FIXME - Stub for now */
   if (!old_path || !*old_path || !new_path || !*new_path)
      return -1;
   return 0;

#else
   /* Every other platform */
   if (!old_path || !*old_path || !new_path || !*new_path)
      return -1;
   return rename(old_path, new_path) == 0 ? 0 : -1;
#endif
}