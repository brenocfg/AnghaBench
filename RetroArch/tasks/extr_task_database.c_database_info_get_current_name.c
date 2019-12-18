#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t list_index; TYPE_2__* list; } ;
typedef  TYPE_3__ database_state_handle_t ;
struct TYPE_6__ {TYPE_1__* elems; } ;
struct TYPE_5__ {char const* data; } ;

/* Variables and functions */

__attribute__((used)) static const char *database_info_get_current_name(
      database_state_handle_t *handle)
{
   if (!handle || !handle->list)
      return NULL;
   return handle->list->elems[handle->list_index].data;
}