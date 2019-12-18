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
typedef  int UINT ;
struct TYPE_3__ {int count; int capacity; int /*<<< orphan*/ ** items; } ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  TYPE_1__ JSON_ARRAY ;

/* Variables and functions */
 int JSON_RET_ERROR ; 
 int JSON_RET_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  parson_free (int /*<<< orphan*/ **) ; 
 scalar_t__ parson_malloc (int) ; 

__attribute__((used)) static UINT json_array_resize(JSON_ARRAY *array, UINT new_capacity) {
	JSON_VALUE **new_items = NULL;
	if (new_capacity == 0) {
		return JSON_RET_ERROR;
	}
	new_items = (JSON_VALUE**)parson_malloc(new_capacity * sizeof(JSON_VALUE*));
	if (new_items == NULL) {
		return JSON_RET_ERROR;
	}
	if (array->items != NULL && array->count > 0) {
		memcpy(new_items, array->items, array->count * sizeof(JSON_VALUE*));
	}
	parson_free(array->items);
	array->items = new_items;
	array->capacity = new_capacity;
	return JSON_RET_OK;
}