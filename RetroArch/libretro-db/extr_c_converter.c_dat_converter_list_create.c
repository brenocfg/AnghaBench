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
struct TYPE_4__ {int capacity; int /*<<< orphan*/ * values; int /*<<< orphan*/ * bt_root; scalar_t__ count; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ dat_converter_list_t ;
typedef  int /*<<< orphan*/  dat_converter_list_item_t ;
typedef  int /*<<< orphan*/  dat_converter_list_enum ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static dat_converter_list_t* dat_converter_list_create(
      dat_converter_list_enum type)
{
   dat_converter_list_t* list = malloc(sizeof(*list));

   list->type                 = type;
   list->count                = 0;
   list->capacity             = (1 << 2);
   list->bt_root              = NULL;
   list->values               = (dat_converter_list_item_t*)malloc(
         sizeof(*list->values) * list->capacity);

   return list;
}