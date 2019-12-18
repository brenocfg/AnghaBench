#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {int items; int count; } ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  TYPE_1__ JSON_ARRAY ;

/* Variables and functions */
 int JSON_RET_ERROR ; 
 int JSON_RET_OK ; 
 int /*<<< orphan*/  JsonArrayGet (TYPE_1__*,int) ; 
 int JsonArrayGetCount (TYPE_1__*) ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int,int,int) ; 

UINT JsonArrayDelete(JSON_ARRAY *array, UINT ix) {
	UINT to_move_bytes = 0;
	if (array == NULL || ix >= JsonArrayGetCount(array)) {
		return JSON_RET_ERROR;
	}
	JsonFree(JsonArrayGet(array, ix));
	to_move_bytes = (JsonArrayGetCount(array) - 1 - ix) * sizeof(JSON_VALUE*);
	memmove(array->items + ix, array->items + ix + 1, to_move_bytes);
	array->count -= 1;
	return JSON_RET_OK;
}