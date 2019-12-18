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
struct TYPE_4__ {int capacity; int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ SignList ;
typedef  int /*<<< orphan*/  Sign ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sign_list_alloc (TYPE_1__*,int) ; 

void sign_list_grow(SignList *list) {
    SignList new_list;
    sign_list_alloc(&new_list, list->capacity * 2);
    memcpy(new_list.data, list->data, list->size * sizeof(Sign));
    free(list->data);
    list->capacity = new_list.capacity;
    list->data = new_list.data;
}