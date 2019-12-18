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
struct TYPE_4__ {int menu_stack_size; int selection_buf_size; int /*<<< orphan*/ ** selection_buf; int /*<<< orphan*/ ** menu_stack; } ;
typedef  TYPE_1__ menu_list_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  menu_list_free (TYPE_1__*) ; 

__attribute__((used)) static menu_list_t *menu_list_new(void)
{
   unsigned i;
   menu_list_t           *list = (menu_list_t*)malloc(sizeof(*list));

   if (!list)
      return NULL;

   list->menu_stack_size       = 1;
   list->selection_buf_size    = 1;
   list->selection_buf         = NULL;
   list->menu_stack            = (file_list_t**)
      calloc(list->menu_stack_size, sizeof(*list->menu_stack));

   if (!list->menu_stack)
      goto error;

   list->selection_buf         = (file_list_t**)
      calloc(list->selection_buf_size, sizeof(*list->selection_buf));

   if (!list->selection_buf)
      goto error;

   for (i = 0; i < list->menu_stack_size; i++)
      list->menu_stack[i]      = (file_list_t*)
         calloc(1, sizeof(*list->menu_stack[i]));

   for (i = 0; i < list->selection_buf_size; i++)
      list->selection_buf[i]   = (file_list_t*)
         calloc(1, sizeof(*list->selection_buf[i]));

   return list;

error:
   menu_list_free(list);
   return NULL;
}