#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct string_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  string_list_capacity (struct string_list*,int) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 

struct string_list *string_list_new(void)
{
   struct string_list *list = (struct string_list*)
      calloc(1, sizeof(*list));

   if (!list)
      return NULL;

   if (!string_list_capacity(list, 32))
   {
      string_list_free(list);
      return NULL;
   }

   return list;
}