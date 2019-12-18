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
struct sun_list {TYPE_1__* last; TYPE_1__* first; } ;
struct TYPE_3__ {struct TYPE_3__* q_forw; struct TYPE_3__* q_back; } ;
typedef  TYPE_1__ qelem ;

/* Variables and functions */

void
sun_list_add(struct sun_list *list, qelem *item)
{
  if (list->last == NULL) {
    list->last = item;
    list->first = item;
    item->q_back = NULL;
  }
  else {
    list->last->q_forw = item;
    item->q_back = list->last;
    list->last = item;
  }

  item->q_forw = NULL;
}