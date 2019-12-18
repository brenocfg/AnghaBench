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
typedef  int /*<<< orphan*/  db_handle_t ;
typedef  int /*<<< orphan*/  database_state_handle_t ;
typedef  int /*<<< orphan*/  database_info_handle_t ;

/* Variables and functions */
#define  DATABASE_TYPE_CRC_LOOKUP 133 
#define  DATABASE_TYPE_ITERATE 132 
#define  DATABASE_TYPE_ITERATE_ARCHIVE 131 
#define  DATABASE_TYPE_ITERATE_LUTRO 130 
#define  DATABASE_TYPE_NONE 129 
#define  DATABASE_TYPE_SERIAL_LOOKUP 128 
 char* database_info_get_current_element_name (int /*<<< orphan*/ *) ; 
 int database_info_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  database_info_set_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ path_contains_compressed_file (char const*) ; 
 int task_database_iterate_crc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int task_database_iterate_playlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int task_database_iterate_playlist_archive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int task_database_iterate_playlist_lutro (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int task_database_iterate_serial_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int task_database_iterate(
      db_handle_t *_db,
      database_state_handle_t *db_state,
      database_info_handle_t *db)
{
   const char *name = database_info_get_current_element_name(db);

   if (!name)
      return 0;

   if (database_info_get_type(db) == DATABASE_TYPE_ITERATE)
      if (path_contains_compressed_file(name))
         database_info_set_type(db, DATABASE_TYPE_ITERATE_ARCHIVE);

   switch (database_info_get_type(db))
   {
      case DATABASE_TYPE_ITERATE:
         return task_database_iterate_playlist(db_state, db, name);
      case DATABASE_TYPE_ITERATE_ARCHIVE:
         return task_database_iterate_playlist_archive(_db, db_state, db, name);
      case DATABASE_TYPE_ITERATE_LUTRO:
         return task_database_iterate_playlist_lutro(_db, db_state, db, name);
      case DATABASE_TYPE_SERIAL_LOOKUP:
         return task_database_iterate_serial_lookup(_db, db_state, db, name);
      case DATABASE_TYPE_CRC_LOOKUP:
         return task_database_iterate_crc_lookup(_db, db_state, db, name, NULL);
      case DATABASE_TYPE_NONE:
      default:
         break;
   }

   return 0;
}