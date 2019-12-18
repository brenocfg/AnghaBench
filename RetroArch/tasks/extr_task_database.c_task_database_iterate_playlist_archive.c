#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  db_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  archive_name; } ;
typedef  TYPE_1__ database_state_handle_t ;
typedef  int /*<<< orphan*/  database_info_handle_t ;

/* Variables and functions */
 int task_database_iterate_crc_lookup (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int task_database_iterate_playlist_archive(
      db_handle_t *_db,
      database_state_handle_t *db_state,
      database_info_handle_t *db, const char *name)
{
#ifdef HAVE_COMPRESSION
   return task_database_iterate_crc_lookup(
         _db, db_state, db, name, db_state->archive_name);
#else
   return 1;
#endif
}