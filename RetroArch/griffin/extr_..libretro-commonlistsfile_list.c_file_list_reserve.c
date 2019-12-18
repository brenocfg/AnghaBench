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
struct item_file {int dummy; } ;
struct TYPE_3__ {size_t capacity; struct item_file* list; } ;
typedef  TYPE_1__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct item_file*,int /*<<< orphan*/ ,size_t const) ; 
 scalar_t__ realloc (struct item_file*,size_t) ; 

bool file_list_reserve(file_list_t *list, size_t nitems)
{
   const size_t item_size = sizeof(struct item_file);
   struct item_file *new_data;

   if (nitems < list->capacity || nitems > (size_t)-1/item_size)
      return false;

   new_data = (struct item_file*)realloc(list->list, nitems * item_size);

   if (!new_data)
      return false;

   memset(&new_data[list->capacity], 0, item_size * (nitems - list->capacity));

   list->list     = new_data;
   list->capacity = nitems;

   return true;
}