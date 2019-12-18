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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ count; } ;
typedef  TYPE_1__ JSON_ARRAY ;

/* Variables and functions */
 scalar_t__ JSON_RET_ERROR ; 
 scalar_t__ JSON_RET_OK ; 
 int /*<<< orphan*/  JsonArrayGet (TYPE_1__*,scalar_t__) ; 
 scalar_t__ JsonArrayGetCount (TYPE_1__*) ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ ) ; 

UINT JsonArrayDeleteAll(JSON_ARRAY *array) {
	UINT i = 0;
	if (array == NULL) {
		return JSON_RET_ERROR;
	}
	for (i = 0; i < JsonArrayGetCount(array); i++) {
		JsonFree(JsonArrayGet(array, i));
	}
	array->count = 0;
	return JSON_RET_OK;
}