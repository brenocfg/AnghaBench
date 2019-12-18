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
struct TYPE_4__ {int /*<<< orphan*/ * path_c; int /*<<< orphan*/  path; int /*<<< orphan*/ * path_b; } ;
typedef  TYPE_1__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_DATABASE_QUERY ; 
 int deferred_push_dlist (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int deferred_push_database_manager_list_deferred(
      menu_displaylist_info_t *info)
{
   if (!string_is_empty(info->path_b))
      free(info->path_b);
   if (!string_is_empty(info->path_c))
      free(info->path_c);

   info->path_b    = strdup(info->path);
   info->path_c    = NULL;

   return deferred_push_dlist(info, DISPLAYLIST_DATABASE_QUERY);
}