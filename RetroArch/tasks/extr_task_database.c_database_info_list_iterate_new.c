#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  info; TYPE_1__* list; scalar_t__ list_index; } ;
typedef  TYPE_2__ database_state_handle_t ;
struct TYPE_5__ {scalar_t__ size; } ;

/* Variables and functions */
 char* database_info_get_current_name (TYPE_2__*) ; 
 int /*<<< orphan*/  database_info_list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  database_info_list_new (char const*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int database_info_list_iterate_new(database_state_handle_t *db_state,
      const char *query)
{
   const char *new_database = database_info_get_current_name(db_state);

#ifndef RARCH_INTERNAL
   fprintf(stderr, "Check database [%d/%d] : %s\n", (unsigned)db_state->list_index,
         (unsigned)db_state->list->size, new_database);
#endif
   if (db_state->info)
   {
      database_info_list_free(db_state->info);
      free(db_state->info);
   }
   db_state->info = database_info_list_new(new_database, query);
   return 0;
}