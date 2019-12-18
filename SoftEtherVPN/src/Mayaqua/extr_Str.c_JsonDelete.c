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
struct TYPE_5__ {int count; int /*<<< orphan*/ * values; int /*<<< orphan*/ * names; } ;
typedef  TYPE_1__ JSON_OBJECT ;

/* Variables and functions */
 size_t JSON_RET_ERROR ; 
 size_t JSON_RET_OK ; 
 int /*<<< orphan*/  JsonFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * JsonGet (TYPE_1__*,char*) ; 
 size_t JsonGetCount (TYPE_1__*) ; 
 int /*<<< orphan*/  parson_free (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

UINT JsonDelete(JSON_OBJECT *object, char *name) {
	UINT i = 0, last_item_index = 0;
	if (object == NULL || JsonGet(object, name) == NULL) {
		return JSON_RET_ERROR;
	}
	last_item_index = JsonGetCount(object) - 1;
	for (i = 0; i < JsonGetCount(object); i++) {
		if (strcmp(object->names[i], name) == 0) {
			parson_free(object->names[i]);
			JsonFree(object->values[i]);
			if (i != last_item_index) { /* Replace key value pair with one from the end */
				object->names[i] = object->names[last_item_index];
				object->values[i] = object->values[last_item_index];
			}
			object->count -= 1;
			return JSON_RET_OK;
		}
	}
	return JSON_RET_ERROR; /* No execution path should end here */
}