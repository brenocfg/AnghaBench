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
struct TYPE_4__ {int count; int size; int /*<<< orphan*/ * array; } ;
typedef  TYPE_1__ ptrlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * my_malloc (int) ; 
 int /*<<< orphan*/ * my_realloc (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static boolean_t
ptrlist_concat(ptrlist_t * list, ptrlist_t * extra)
{
    if (extra->count == 0)
	return (TRUE);

    if ((extra->count + list->count) > list->size) {
	int old_size = list->size;

	list->size = extra->count + list->count;
	if (list->array == NULL)
	    list->array = my_malloc(sizeof(*list->array) * list->size);
	else
	    list->array = my_realloc(list->array, old_size,
				     sizeof(*list->array) * list->size);
    }
    if (list->array == NULL)
	return (FALSE);
    bcopy(extra->array, list->array + list->count, 
	  extra->count * sizeof(*list->array));
    list->count += extra->count;
    return (TRUE);
}