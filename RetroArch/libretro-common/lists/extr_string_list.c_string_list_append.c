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
typedef  union string_list_elem_attr {int dummy; } string_list_elem_attr ;
struct string_list {int size; int cap; TYPE_1__* elems; } ;
struct TYPE_2__ {char* data; union string_list_elem_attr attr; } ;

/* Variables and functions */
 char* strdup (char const*) ; 
 int /*<<< orphan*/  string_list_capacity (struct string_list*,int) ; 

bool string_list_append(struct string_list *list, const char *elem,
      union string_list_elem_attr attr)
{
   char *data_dup = NULL;

   if (list->size >= list->cap &&
         !string_list_capacity(list, list->cap * 2))
      return false;

   data_dup = strdup(elem);
   if (!data_dup)
      return false;

   list->elems[list->size].data = data_dup;
   list->elems[list->size].attr = attr;

   list->size++;
   return true;
}