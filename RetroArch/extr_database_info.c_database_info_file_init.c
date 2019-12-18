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
union string_list_elem_attr {scalar_t__ i; } ;
struct string_list {int dummy; } ;
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  enum database_type { ____Placeholder_database_type } database_type ;
struct TYPE_4__ {int type; int /*<<< orphan*/  status; struct string_list* list; scalar_t__ list_ptr; } ;
typedef  TYPE_1__ database_info_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATABASE_STATUS_ITERATE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*,union string_list_elem_attr) ; 
 struct string_list* string_list_new () ; 

database_info_handle_t *database_info_file_init(const char *path,
      enum database_type type, retro_task_t *task)
{
   union string_list_elem_attr attr;
   struct string_list        *list  = NULL;
   database_info_handle_t      *db  = (database_info_handle_t*)
      calloc(1, sizeof(*db));

   if (!db)
      return NULL;

   attr.i             = 0;

   list               = string_list_new();

   if (!list)
   {
      free(db);
      return NULL;
   }

   string_list_append(list, path, attr);

   db->list_ptr       = 0;
   db->list           = list;
   db->status         = DATABASE_STATUS_ITERATE;
   db->type           = type;

   return db;
}