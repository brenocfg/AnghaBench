#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; TYPE_1__* elems; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ string_is_equal_noncase (int /*<<< orphan*/ ,char const*) ; 

int string_list_find_elem(const struct string_list *list, const char *elem)
{
   size_t i;

   if (!list)
      return false;

   for (i = 0; i < list->size; i++)
   {
      if (string_is_equal_noncase(list->elems[i].data, elem))
         return (int)(i + 1);
   }

   return false;
}