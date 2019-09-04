#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tre_mem_t ;
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* data; struct TYPE_5__* blocks; } ;
typedef  TYPE_1__ tre_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void
tre_mem_destroy(tre_mem_t mem)
{
  tre_list_t *tmp, *l = mem->blocks;

  while (l != NULL)
    {
      xfree(l->data);
      tmp = l->next;
      xfree(l);
      l = tmp;
    }
  xfree(mem);
}