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
typedef  size_t UINT ;
struct TYPE_5__ {size_t count; struct TYPE_5__* items; } ;
typedef  TYPE_1__ JSON_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  JsonFree (TYPE_1__) ; 
 int /*<<< orphan*/  parson_free (TYPE_1__*) ; 

__attribute__((used)) static void json_array_free(JSON_ARRAY *array) {
	UINT i;
	for (i = 0; i < array->count; i++) {
		JsonFree(array->items[i]);
	}
	parson_free(array->items);
	parson_free(array);
}