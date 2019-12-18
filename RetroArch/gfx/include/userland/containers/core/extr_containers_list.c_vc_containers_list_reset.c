#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; scalar_t__ capacity; } ;
typedef  TYPE_1__ VC_CONTAINERS_LIST_T ;

/* Variables and functions */

void vc_containers_list_reset(VC_CONTAINERS_LIST_T *list)
{
   /* Avoid trying to reset read-only lists */
   if (list && list->capacity)
      list->size = 0;
}