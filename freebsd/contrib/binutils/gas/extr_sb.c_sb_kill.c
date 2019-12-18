#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t pot; TYPE_1__* item; } ;
typedef  TYPE_2__ sb ;
struct TYPE_7__ {TYPE_1__** size; } ;
struct TYPE_5__ {struct TYPE_5__* next; } ;

/* Variables and functions */
 TYPE_4__ free_list ; 

void
sb_kill (sb *ptr)
{
  /* Return item to free list.  */
  ptr->item->next = free_list.size[ptr->pot];
  free_list.size[ptr->pot] = ptr->item;
}