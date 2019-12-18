#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct string_list {scalar_t__ size; TYPE_1__* elems; } ;
struct TYPE_7__ {scalar_t__ crc; scalar_t__ archive_crc; scalar_t__ entry_index; scalar_t__ list_index; } ;
typedef  TYPE_2__ database_state_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_3__ database_info_handle_t ;
struct TYPE_6__ {char const* data; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 struct string_list* file_archive_get_file_list (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  path_contains_compressed_file (char const*) ; 
 scalar_t__ path_is_compressed_file (char const*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int database_info_list_iterate_end_no_match(
      database_info_handle_t *db,
      database_state_handle_t *db_state,
      const char *path)
{
   /* Reached end of database list,
    * CRC match probably didn't succeed. */

   /* If this was a compressed file and no match in the database
    * list was found then expand the search list to include the
    * archive's contents. */
   if (path_is_compressed_file(path) && !path_contains_compressed_file(path))
   {
      struct string_list *archive_list =
         file_archive_get_file_list(path, NULL);

      if (archive_list && archive_list->size > 0)
      {
         unsigned i;

         for (i = 0; i < archive_list->size; i++)
         {
            char *new_path   = (char*)malloc(
               PATH_MAX_LENGTH * sizeof(char));
            size_t path_size = PATH_MAX_LENGTH * sizeof(char);
            size_t path_len  = strlen(path);

            new_path[0] = '\0';

            strlcpy(new_path, path, path_size);

            if (path_len + strlen(archive_list->elems[i].data)
                     + 1 < PATH_MAX_LENGTH)
            {
               new_path[path_len] = '#';
               strlcpy(new_path + path_len + 1,
                  archive_list->elems[i].data,
                  path_size - path_len);
            }

            string_list_append(db->list, new_path,
               archive_list->elems[i].attr);

            free(new_path);
         }

         string_list_free(archive_list);
      }
   }

   db_state->list_index  = 0;
   db_state->entry_index = 0;

   if (db_state->crc != 0)
      db_state->crc = 0;

   if (db_state->archive_crc != 0)
      db_state->archive_crc = 0;

   return 0;
}