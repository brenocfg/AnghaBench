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
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/ ** items; } ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  TYPE_1__ JSON_ARRAY ;

/* Variables and functions */
 size_t JsonArrayGetCount (TYPE_1__*) ; 

JSON_VALUE * JsonArrayGet(JSON_ARRAY *array, UINT index) {
	if (array == NULL || index >= JsonArrayGetCount(array)) {
		return NULL;
	}
	return array->items[index];
}