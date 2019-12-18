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
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_4__ {int size; scalar_t__ index; } ;
typedef  TYPE_1__ rarch_setting_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * menu_setting_new_internal (TYPE_1__*) ; 

__attribute__((used)) static rarch_setting_t *menu_setting_new(void)
{
   rarch_setting_t* list           = NULL;
   rarch_setting_info_t *list_info = (rarch_setting_info_t*)
      malloc(sizeof(*list_info));

   if (!list_info)
      return NULL;

   list_info->index = 0;
   list_info->size  = 32;

   list             = menu_setting_new_internal(list_info);

   if (list_info)
      free(list_info);

   list_info        = NULL;

   return list;
}