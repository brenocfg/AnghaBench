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
typedef  TYPE_1__* attrs ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  attrs_pool ; 
 int /*<<< orphan*/  pool_free (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
attrs_list_clear (attrs *listp)
{
  attrs list, next;

  for (list = *listp; list; list = next)
    {
      next = list->next;
      pool_free (attrs_pool, list);
    }
  *listp = NULL;
}