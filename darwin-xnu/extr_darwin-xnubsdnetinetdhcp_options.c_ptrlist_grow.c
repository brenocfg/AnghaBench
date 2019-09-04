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
struct TYPE_3__ {int size; int count; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ ptrlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int PTRLIST_NUMBER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/ * my_malloc (int) ; 
 int /*<<< orphan*/ * my_realloc (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static boolean_t
ptrlist_grow(ptrlist_t * list)
{
    if (list->array == NULL) {
	if (list->size == 0)
	    list->size = PTRLIST_NUMBER;
	list->count = 0;
	list->array = my_malloc(sizeof(*list->array) * list->size);
    }
    else if (list->size == list->count) {
	dprintf(("doubling %d to %d\n", list->size, list->size * 2));
	list->array = my_realloc(list->array, 
				 sizeof(*list->array) * list->size,
				 sizeof(*list->array) * list->size * 2);
	list->size *= 2;
    }
    if (list->array == NULL)
	return (FALSE);
    return (TRUE);
}