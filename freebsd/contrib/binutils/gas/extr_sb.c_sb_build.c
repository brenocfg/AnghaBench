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
struct TYPE_5__ {int size; int /*<<< orphan*/  data; struct TYPE_5__* next; } ;
typedef  TYPE_1__ sb_element ;
struct TYPE_6__ {int pot; TYPE_1__* item; scalar_t__ len; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ sb ;
struct TYPE_7__ {TYPE_1__** size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ free_list ; 
 int sb_max_power_two ; 
 int /*<<< orphan*/ * string_count ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
sb_build (sb *ptr, int size)
{
  /* See if we can find one to allocate.  */
  sb_element *e;

  assert (size < sb_max_power_two);

  e = free_list.size[size];
  if (!e)
    {
      /* Nothing there, allocate one and stick into the free list.  */
      e = (sb_element *) xmalloc (sizeof (sb_element) + (1 << size));
      e->next = free_list.size[size];
      e->size = 1 << size;
      free_list.size[size] = e;
      string_count[size]++;
    }

  /* Remove from free list.  */
  free_list.size[size] = e->next;

  /* Copy into callers world.  */
  ptr->ptr = e->data;
  ptr->pot = size;
  ptr->len = 0;
  ptr->item = e;
}