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
struct TYPE_3__ {int /*<<< orphan*/  free_cb; scalar_t__ length; int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ list_t ;
typedef  int /*<<< orphan*/  list_free_cb ;

/* Variables and functions */
 scalar_t__ osi_calloc (int) ; 

list_t *list_new_internal(list_free_cb callback)
{
    list_t *list = (list_t *) osi_calloc(sizeof(list_t));
    if (!list) {
        return NULL;
    }

    list->head = list->tail = NULL;
    list->length = 0;
    list->free_cb = callback;
    return list;
}