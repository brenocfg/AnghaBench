#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct stat {int /*<<< orphan*/  st_mode; scalar_t__ st_size; } ;
struct _stat {scalar_t__ st_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; scalar_t__ size; } ;
typedef  TYPE_1__ iox_stat_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {int st_mode; scalar_t__ st_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  st_mode; scalar_t__ st_size; } ;
typedef  TYPE_2__ SceIoStat ;
typedef  int DWORD ;
typedef  TYPE_3__ CellFsStat ;

/* Variables and functions */
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FIO_S_ISDIR (int /*<<< orphan*/ ) ; 
 int GetFileAttributes (char*) ; 
 int GetFileAttributesW (char*) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int RETRO_VFS_STAT_IS_CHARACTER_SPECIAL ; 
 int RETRO_VFS_STAT_IS_DIRECTORY ; 
 int RETRO_VFS_STAT_IS_VALID ; 
 int S_IFDIR ; 
 int S_IFMT ; 
 int S_ISCHR (int /*<<< orphan*/ ) ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _stat (char*,struct _stat*) ; 
 int /*<<< orphan*/  _wstat (char*,struct _stat*) ; 
 scalar_t__ cellFsStat (char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  fileXioDclose (int) ; 
 int fileXioDopen (char const*) ; 
 int /*<<< orphan*/  fileXioGetStat (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  orbisDclose (int) ; 
 int orbisDopen (char const*) ; 
 int sceIoGetstat (char*,TYPE_2__*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 size_t strlen (char*) ; 
 char* utf8_to_local_string_alloc (char const*) ; 
 char* utf8_to_utf16_string_alloc (char const*) ; 

int retro_vfs_stat_impl(const char *path, int32_t *size)
{
#if defined(VITA) || defined(PSP)
   /* Vita / PSP */
   SceIoStat buf;
   int stat_ret;
   bool is_dir               = false;
   bool is_character_special = false;
   char *tmp                 = NULL;
   size_t len                = 0;

   if (!path || !*path)
      return 0;

   tmp                       = strdup(path);
   len                       = strlen(tmp);
   if (tmp[len-1] == '/')
      tmp[len-1] = '\0';

   stat_ret = sceIoGetstat(tmp, &buf);
   free(tmp);
   if (stat_ret < 0)
      return 0;

   if (size)
      *size = (int32_t)buf.st_size;

   is_dir = FIO_S_ISDIR(buf.st_mode);

   return RETRO_VFS_STAT_IS_VALID | (is_dir ? RETRO_VFS_STAT_IS_DIRECTORY : 0) | (is_character_special ? RETRO_VFS_STAT_IS_CHARACTER_SPECIAL : 0);

#elif defined(ORBIS)
   /* Orbis */
   bool is_dir, is_character_special;
   int dir_ret;

   if (!path || !*path)
      return 0;

   if (size)
      *size = (int32_t)buf.st_size;

   dir_ret = orbisDopen(path);
   is_dir  = dir_ret > 0;
   orbisDclose(dir_ret);

   is_character_special = S_ISCHR(buf.st_mode);

   return RETRO_VFS_STAT_IS_VALID | (is_dir ? RETRO_VFS_STAT_IS_DIRECTORY : 0) | (is_character_special ? RETRO_VFS_STAT_IS_CHARACTER_SPECIAL : 0);

#elif defined(PS2)
   /* PS2 */
   iox_stat_t buf;
   bool is_dir;
   bool is_character_special = false;
   char *tmp                 = NULL;
   size_t len                = 0;

   if (!path || !*path)
      return 0;

   tmp        = strdup(path);
   len        = strlen(tmp);
   if (tmp[len-1] == '/')
      tmp[len-1] = '\0';

   fileXioGetStat(tmp, &buf);
   free(tmp);

   if (size)
      *size = (int32_t)buf.size;

   if (!buf.mode)
   {
      /* if fileXioGetStat fails */
      int dir_ret = fileXioDopen(path);
      is_dir      =  dir_ret > 0;
      if (is_dir) {
         fileXioDclose(dir_ret);
      }
   }
   else
      is_dir = FIO_S_ISDIR(buf.mode);

   return RETRO_VFS_STAT_IS_VALID | (is_dir ? RETRO_VFS_STAT_IS_DIRECTORY : 0) | (is_character_special ? RETRO_VFS_STAT_IS_CHARACTER_SPECIAL : 0);

#elif defined(__CELLOS_LV2__)
   /* CellOS Lv2 */
   bool is_dir;
   bool is_character_special = false;
   CellFsStat buf;

   if (!path || !*path)
      return 0;
   if (cellFsStat(path, &buf) < 0)
      return 0;

   if (size)
      *size = (int32_t)buf.st_size;

   is_dir = ((buf.st_mode & S_IFMT) == S_IFDIR);

   return RETRO_VFS_STAT_IS_VALID | (is_dir ? RETRO_VFS_STAT_IS_DIRECTORY : 0) | (is_character_special ? RETRO_VFS_STAT_IS_CHARACTER_SPECIAL : 0);

#elif defined(_WIN32)
   /* Windows */
   bool is_dir;
   DWORD file_info;
   struct _stat buf;
   bool is_character_special = false;
#if defined(LEGACY_WIN32)
   char *path_local          = NULL;
#else
   wchar_t *path_wide        = NULL;
#endif

   if (!path || !*path)
      return 0;

#if defined(LEGACY_WIN32)
   path_local = utf8_to_local_string_alloc(path);
   file_info  = GetFileAttributes(path_local);

   if (!string_is_empty(path_local))
      _stat(path_local, &buf);

   if (path_local)
      free(path_local);
#else
   path_wide = utf8_to_utf16_string_alloc(path);
   file_info = GetFileAttributesW(path_wide);

   _wstat(path_wide, &buf);

   if (path_wide)
      free(path_wide);
#endif

   if (file_info == INVALID_FILE_ATTRIBUTES)
      return 0;

   if (size)
      *size = (int32_t)buf.st_size;

   is_dir = (file_info & FILE_ATTRIBUTE_DIRECTORY);

   return RETRO_VFS_STAT_IS_VALID | (is_dir ? RETRO_VFS_STAT_IS_DIRECTORY : 0) | (is_character_special ? RETRO_VFS_STAT_IS_CHARACTER_SPECIAL : 0);

#else
   /* Every other platform */
   bool is_dir, is_character_special;
   struct stat buf;

   if (!path || !*path)
      return 0;
   if (stat(path, &buf) < 0)
      return 0;

   if (size)
      *size             = (int32_t)buf.st_size;

   is_dir               = S_ISDIR(buf.st_mode);
   is_character_special = S_ISCHR(buf.st_mode);

   return RETRO_VFS_STAT_IS_VALID | (is_dir ? RETRO_VFS_STAT_IS_DIRECTORY : 0) | (is_character_special ? RETRO_VFS_STAT_IS_CHARACTER_SPECIAL : 0);
#endif
}