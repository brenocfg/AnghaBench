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
struct TYPE_5__ {TYPE_1__* list; } ;
typedef  TYPE_2__ file_list_t ;
struct TYPE_4__ {int /*<<< orphan*/ * alt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

void file_list_set_alt_at_offset(file_list_t *list, size_t idx,
      const char *alt)
{
   if (!list || !alt)
      return;

   if (list->list[idx].alt)
      free(list->list[idx].alt);
   list->list[idx].alt      = NULL;

   if (alt)
      list->list[idx].alt   = strdup(alt);
}