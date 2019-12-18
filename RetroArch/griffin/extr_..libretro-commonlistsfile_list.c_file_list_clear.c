#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; TYPE_1__* list; } ;
typedef  TYPE_2__ file_list_t ;
struct TYPE_4__ {int /*<<< orphan*/ * alt; int /*<<< orphan*/ * label; int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void file_list_clear(file_list_t *list)
{
   size_t i;

   if (!list)
      return;

   for (i = 0; i < list->size; i++)
   {
      if (list->list[i].path)
         free(list->list[i].path);
      list->list[i].path = NULL;

      if (list->list[i].label)
         free(list->list[i].label);
      list->list[i].label = NULL;

      if (list->list[i].alt)
         free(list->list[i].alt);
      list->list[i].alt = NULL;
   }

   list->size = 0;
}