#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* serial; int /*<<< orphan*/  crc; int /*<<< orphan*/  archive_crc; } ;
typedef  TYPE_1__ database_state_handle_t ;
typedef  int /*<<< orphan*/  database_info_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATABASE_TYPE_CRC_LOOKUP ; 
 int /*<<< orphan*/  DATABASE_TYPE_ITERATE_LUTRO ; 
 int /*<<< orphan*/  DATABASE_TYPE_SERIAL_LOOKUP ; 
#define  FILE_TYPE_CHD 134 
#define  FILE_TYPE_COMPRESSED 133 
#define  FILE_TYPE_CUE 132 
#define  FILE_TYPE_GDI 131 
#define  FILE_TYPE_ISO 130 
#define  FILE_TYPE_LUTRO 129 
#define  FILE_TYPE_WBFS 128 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  database_info_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int extension_to_file_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdi_prune (int /*<<< orphan*/ *,char const*) ; 
 int intfstream_file_get_crc (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intfstream_file_get_serial (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 int task_database_chd_get_crc (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_database_chd_get_serial (char const*,char*) ; 
 int task_database_cue_get_crc (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_database_cue_get_serial (char const*,char*) ; 
 int /*<<< orphan*/  task_database_cue_prune (int /*<<< orphan*/ *,char const*) ; 
 int task_database_gdi_get_crc (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_database_gdi_get_serial (char const*,char*) ; 

__attribute__((used)) static int task_database_iterate_playlist(
      database_state_handle_t *db_state,
      database_info_handle_t *db, const char *name)
{
   switch (extension_to_file_type(path_get_extension(name)))
   {
      case FILE_TYPE_COMPRESSED:
#ifdef HAVE_COMPRESSION
         database_info_set_type(db, DATABASE_TYPE_CRC_LOOKUP);
         /* first check crc of archive itself */
         return intfstream_file_get_crc(name,
               0, SIZE_MAX, &db_state->archive_crc);
#else
         break;
#endif
      case FILE_TYPE_CUE:
         task_database_cue_prune(db, name);
         db_state->serial[0] = '\0';
         if (task_database_cue_get_serial(name, db_state->serial))
            database_info_set_type(db, DATABASE_TYPE_SERIAL_LOOKUP);
         else
         {
            database_info_set_type(db, DATABASE_TYPE_CRC_LOOKUP);
            return task_database_cue_get_crc(name, &db_state->crc);
         }
         break;
      case FILE_TYPE_GDI:
         gdi_prune(db, name);
         db_state->serial[0] = '\0';
         /* There are no serial databases, so don't bother with
            serials at the moment */
         if (0 && task_database_gdi_get_serial(name, db_state->serial))
            database_info_set_type(db, DATABASE_TYPE_SERIAL_LOOKUP);
         else
         {
            database_info_set_type(db, DATABASE_TYPE_CRC_LOOKUP);
            return task_database_gdi_get_crc(name, &db_state->crc);
         }
         break;
      /* Consider Wii WBFS files similar to ISO files. */
      case FILE_TYPE_WBFS:
      case FILE_TYPE_ISO:
         db_state->serial[0] = '\0';
         intfstream_file_get_serial(name, 0, SIZE_MAX, db_state->serial);
         database_info_set_type(db, DATABASE_TYPE_SERIAL_LOOKUP);
         break;
      case FILE_TYPE_CHD:
         db_state->serial[0] = '\0';
         if (task_database_chd_get_serial(name, db_state->serial))
            database_info_set_type(db, DATABASE_TYPE_SERIAL_LOOKUP);
         else
         {
            database_info_set_type(db, DATABASE_TYPE_CRC_LOOKUP);
            return task_database_chd_get_crc(name, &db_state->crc);
         }
         break;
      case FILE_TYPE_LUTRO:
         database_info_set_type(db, DATABASE_TYPE_ITERATE_LUTRO);
         break;
      default:
         database_info_set_type(db, DATABASE_TYPE_CRC_LOOKUP);
         return intfstream_file_get_crc(name, 0, SIZE_MAX, &db_state->crc);
   }

   return 1;
}